#pragma once

#include "shared.hpp"

#include <glm/glm.hpp>
#include <vector>
#include <memory>

namespace MyEngine::Physics
{
    class Body2D
    {
    public:
        Body2D(std::vector<glm::vec2> const& t_vertecies, bool t_isDynamic);
        Body2D(std::vector<float> const& t_vertecies, bool t_isDynamic);
        Body2D(std::vector<glm::vec2> && t_vertecies, bool t_isDynamic);

        void applyMovementStep(float t_time = 1);
        void applyTranslation(glm::vec2&& t_translation);
        void undoLastTranslation(float t_bounce = 1);

        glm::vec2 getMovementDirection()
            { return m_velocity + m_groupVelocity + (m_acceleration + m_groupAcceleration) * 0.5f; }

        inline void addGroupVelocity(glm::vec2& t_groupVelocity)
            { m_groupVelocity += t_groupVelocity; }
        inline void addGroupAcceleartion(glm::vec2& t_groupAcceleration)
            { m_groupAcceleration += t_groupAcceleration; }
        inline void setAssociatedModel(std::shared_ptr<glm::mat4> t_model)
            { m_model = t_model; }
        inline glm::vec2& acceleration()
            { return m_acceleration; }
        inline glm::vec2& velocity()
            { return m_velocity; }
        inline glm::vec2 lastTranslation() const
            { return m_lastTranslation; }
        inline glm::vec2 center() const
            { return m_center; }

        inline bool isStatic() const
            { return !m_dynamic; }
        inline bool isDynamic() const
            { return m_dynamic; }

        CollisionInfo checkCollision(Body2D& t_body, CollisionLevel t_collisionLevel);
        CollisionInfo checkInclusion(glm::vec2&& t_vertex);
        CollisionInfo checkBC(Body2D& t_body);
        CollisionInfo checkAABB(Body2D& t_body);
        CollisionInfo checkOutOfBounds(Body2D& t_body);
        CollisionInfo checkEdges(Body2D& t_body);
        CollisionInfo checkEdge(glm::vec2& t_a, glm::vec2& t_b);
        // CollisionInfo checkEdgeInfluence(glm::vec2& t_center, float radius);
        // CollisionInfo checkEdgeInfluence();

    private:
        void calculateBindingCircle();
        void calculateAABBB();
        void calculateEdgeInfluence();

        std::shared_ptr<glm::mat4> m_model;

        glm::vec2 m_lastTranslation = glm::vec2(0);
        glm::vec2 m_acceleration = glm::vec2(0);
        glm::vec2 m_velocity = glm::vec2(0);
        glm::vec2 m_groupAcceleration = glm::vec2(0);
        glm::vec2 m_groupVelocity = glm::vec2(0);

        bool m_axisAlligned;
        bool m_dynamic;

        float m_upperBound;
        float m_lowerBound;
        float m_leftBound;
        float m_rightBound;

        glm::vec2 m_center;
        float m_radius;

        std::vector<glm::vec2> m_vertecies;
        // std::vector<glm::mat2> m_edgeInfluenceBases;
        // std::vector<float> m_edgeInfluenceLengths;
    };
}