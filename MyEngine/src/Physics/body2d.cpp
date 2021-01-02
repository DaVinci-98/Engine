#include "Physics/body2D.hpp"

#include <numeric>
#include <algorithm>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

namespace MyEngine::Physics
{
    Body2D::Body2D(std::vector<float> const& t_vertecies, bool t_isDynamic)
    {
        std::vector<glm::vec2> vertecies;
        for(int i = 0; i < t_vertecies.size(); i+=2)
            vertecies.push_back(glm::vec2(t_vertecies[i], t_vertecies[i+1]));

        m_vertecies = vertecies;
        m_dynamic = t_isDynamic;

        calculateBindingCircle();
        calculateAABBB();
    }

    Body2D::Body2D(std::vector<glm::vec2> const& t_vertecies, bool t_isDynamic)
    {
        m_vertecies = t_vertecies;
        m_dynamic = t_isDynamic;

        calculateBindingCircle();
        calculateAABBB();
    }

    Body2D::Body2D(std::vector<glm::vec2> && t_vertecies, bool t_isDynamic)
    {
        m_vertecies = std::move(t_vertecies);
        m_dynamic = t_isDynamic;

        calculateBindingCircle();
        calculateAABBB();
    }

    void Body2D::calculateBindingCircle()
    {
        m_center = std::accumulate(m_vertecies.begin(), m_vertecies.end(), glm::vec2(0)) / static_cast<float>(m_vertecies.size());

        m_radius = 0;
        for(auto& vertex : m_vertecies)
        {
            float dist = glm::distance(m_center, vertex);
            if(dist > m_radius) m_radius = dist;
        }
    }

    void Body2D::calculateAABBB()
    {
        m_upperBound = m_vertecies[0].y;
        m_lowerBound = m_vertecies[0].y;
        m_leftBound  = m_vertecies[0].x;
        m_rightBound = m_vertecies[0].x;

        for(auto& vertex : m_vertecies)
        {
            if(m_upperBound < vertex.y) m_upperBound = vertex.y;
            if(m_lowerBound > vertex.y) m_lowerBound = vertex.y;
            if(m_rightBound < vertex.x) m_rightBound = vertex.x;
            if(m_leftBound  > vertex.x) m_leftBound  = vertex.x;
        }

        if(m_vertecies.size() == 4)
        {
            for(auto& vertex : m_vertecies)
            {
                if((m_upperBound != vertex.y && m_lowerBound != vertex.y) ||
                   (m_rightBound != vertex.x && m_leftBound  != vertex.x))
                {
                    m_axisAlligned = false;
                    return;
                }
            }
        }
        else m_axisAlligned = false;
    }

    void Body2D::applyMovementStep(float t_time)
    {
        glm::vec2 acceleration = m_acceleration + m_groupAcceleration;
        glm::vec2 startVelocity = m_velocity + m_groupVelocity;
        glm::vec2 translation = startVelocity * t_time + acceleration * t_time * t_time / 2.0f;

        applyTranslation(std::move(translation));

        m_velocity += acceleration * t_time;

        m_groupAcceleration = glm::vec2(0);
        m_groupVelocity = glm::vec2(0);
    }

    void Body2D::applyTranslation(glm::vec2&& t_translation)
    {
        m_lastTranslation = t_translation;
        
        for(auto& vertex : m_vertecies)
            vertex += t_translation;
        
        m_center += t_translation;

        m_lowerBound += t_translation.y;
        m_upperBound += t_translation.y;
        m_leftBound  += t_translation.x;
        m_rightBound += t_translation.x;

        if(m_model)
            *m_model = glm::translate(*m_model, glm::vec3(t_translation, 0));
    }

    void Body2D::undoLastTranslation(float t_bounce)
    { 
        float len = glm::length(m_lastTranslation);
        if(len == 0) return;

        float scale = t_bounce * (len + 1.0f) / len;
        applyTranslation(- scale * m_lastTranslation);
        m_lastTranslation = glm::vec2(0);
    }

    CollisionInfo Body2D::checkCollision(Body2D& t_body, CollisionLevel t_collisionLevel)
    {
        switch (t_collisionLevel)
        {
        case CIRCLE_BOUND:
            return checkBC(t_body);
            break;
        case AXIS_ALLIGNED_BOUNDING_BOX:
            return checkAABB(t_body);
            break;
        case EDGE_COLLISION:
            return checkEdges(t_body);
            break;
        case OUT_OF_BOUNDS:
            return checkOutOfBounds(t_body);
            break;
        default:
            return CollisionInfo { false };
            break;
        }
    }

    CollisionInfo Body2D::checkOutOfBounds(Body2D& t_body)
    {
        CollisionInfo info;
        info.m_detected = false;
        info.m_penetration = glm::vec2(0);
        if (m_upperBound > t_body.m_upperBound)
        {
            info.m_detected = true;
            info.m_collisionPoints.push_back(glm::vec2(0, m_upperBound - t_body.m_upperBound));
            info.m_penetration += info.m_collisionPoints.back();
        }
        else if (m_lowerBound < t_body.m_lowerBound)
        {
            info.m_detected = true;
            info.m_collisionPoints.push_back(glm::vec2(0, m_lowerBound - t_body.m_lowerBound));
            info.m_penetration += info.m_collisionPoints.back();
        }
        if (m_rightBound > t_body.m_rightBound)
        {
            info.m_detected = true;
            info.m_collisionPoints.push_back(glm::vec2(m_rightBound - t_body.m_rightBound, 0));
            info.m_penetration += info.m_collisionPoints.back();
        }
        else if (m_leftBound  < t_body.m_leftBound )
        {
            info.m_detected = true;
            info.m_collisionPoints.push_back(glm::vec2(m_leftBound - t_body.m_leftBound,   0));
            info.m_penetration += info.m_collisionPoints.back();
        }
        return info;
    }

    CollisionInfo Body2D::checkEdge(glm::vec2& t_a, glm::vec2& t_b)
    {
        auto extA = glm::vec3(t_a, 1);
        auto extB = glm::vec3(t_b, 1);
        for(std::size_t i = 0; i < m_vertecies.size(); i++)
        {
            std::size_t leftIdx = i;
            std::size_t rightIdx = (i + 1) % m_vertecies.size();

            auto extLeft = glm::vec3(m_vertecies[leftIdx], 1);
            auto extRight = glm::vec3(m_vertecies[rightIdx], 1);

            float area = glm::determinant(glm::mat<3,3,float>(extA, extLeft, extRight));
            float s = glm::determinant(glm::mat<3,3,float>(extLeft,  extRight, extB)) / area;
            float t = glm::determinant(glm::mat<3,3,float>(extRight, extA,     extB)) / area;
            float u = glm::determinant(glm::mat<3,3,float>(extA,     extLeft,  extB)) / area;

            if(s <= 0 && t >= 0 && u >= 0)
                return CollisionInfo { true };
        }

        return CollisionInfo { false };
    }


    CollisionInfo Body2D::checkInclusion(glm::vec2&& t_vertex)
    {
        auto extCenter = glm::vec3(m_center, 1);
        for(std::size_t i = 0; i < m_vertecies.size(); i++)
        {
            std::size_t leftIdx = i;
            std::size_t rightIdx = (i + 1) % m_vertecies.size();

            auto extLeft = glm::vec3(m_vertecies[leftIdx], 1);
            auto extRight = glm::vec3(m_vertecies[rightIdx], 1);
            auto extVertex = glm::vec3(t_vertex, 1);

            float area = glm::determinant(glm::mat<3,3,float>(extCenter, extLeft, extRight));
            float s = glm::determinant(glm::mat<3,3,float>(extLeft,   extRight,  extVertex)) / area;
            float t = glm::determinant(glm::mat<3,3,float>(extRight,  extCenter, extVertex)) / area;
            float u = glm::determinant(glm::mat<3,3,float>(extCenter, extLeft,   extVertex)) / area;

            if(s <= 1 && s >= 0 &&
               t <= 1 && t >= 0 &&
               u <= 1 && t >= 0)
            {
                return CollisionInfo { true };
            } 
        }

        return CollisionInfo { false };
    }

    CollisionInfo Body2D::checkBC(Body2D& t_body)
    {
        float distance = glm::distance(m_center, t_body.m_center);
        float allowedDistance = m_radius + t_body.m_radius;

        return CollisionInfo { .m_detected = distance < allowedDistance };
    }

    CollisionInfo Body2D::checkAABB(Body2D& t_body)
    {

        CollisionInfo info;
        info.m_detected = false;
        info.m_penetration = glm::vec2(0);

        if(m_leftBound  < t_body.m_rightBound &&
           m_rightBound > t_body.m_leftBound)
        {
            if(m_lowerBound < t_body.m_upperBound && 
               m_lowerBound > t_body.m_lowerBound && 
               m_upperBound > t_body.m_upperBound)
            {
                info.m_detected = true;
                info.m_collisionPoints.push_back(glm::vec2(0, m_lowerBound - t_body.m_upperBound));
                info.m_penetration += info.m_collisionPoints.back();
            }
            else if(m_upperBound > t_body.m_lowerBound && 
                    m_upperBound < t_body.m_upperBound && 
                    m_lowerBound < t_body.m_lowerBound)
            {
                info.m_detected = true;
                info.m_collisionPoints.push_back(glm::vec2(0, m_upperBound - t_body.m_lowerBound));
                info.m_penetration += info.m_collisionPoints.back();
            }
        }
        if(m_lowerBound < t_body.m_upperBound &&
           m_upperBound > t_body.m_lowerBound)
        {
            if(m_leftBound  < t_body.m_rightBound && 
               m_leftBound  > t_body.m_leftBound  && 
               m_rightBound > t_body.m_rightBound)
            {
                info.m_detected = true;
                info.m_collisionPoints.push_back(glm::vec2(m_leftBound - t_body.m_rightBound,  0));
                info.m_penetration += info.m_collisionPoints.back();
            }
            else if(m_rightBound > t_body.m_leftBound  && 
                    m_rightBound < t_body.m_rightBound && 
                    m_leftBound  < t_body.m_leftBound) 
            {
                info.m_detected = true;
                info.m_collisionPoints.push_back(glm::vec2(m_rightBound - t_body.m_leftBound,  0));
                info.m_penetration += info.m_collisionPoints.back();
            }   
        }
        return info;
    }

    CollisionInfo Body2D::checkEdges(Body2D& t_body)
    {
        if(t_body.m_axisAlligned && m_axisAlligned) return checkAABB(t_body);

        for(std::size_t i = 0; i < t_body.m_vertecies.size(); i++)
        {
            std::size_t leftIdx = i;
            std::size_t rightIdx = (i + 1) % t_body.m_vertecies.size();

            CollisionInfo info = checkEdge(t_body.m_vertecies[leftIdx], t_body.m_vertecies[rightIdx]);
            if(info.m_detected) return info;
        }
        
        return CollisionInfo { false };
    }
}