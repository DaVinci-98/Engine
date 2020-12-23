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
        Body2D(std::vector<glm::vec2> && t_vertecies, bool t_isDynamic);

        void applyMovementStep(glm::vec2&& t_ambientVelocity = glm::vec2(0), glm::vec2&& t_ambientAcceleartion = glm::vec2(0), float t_time = 1);
        void applyMovementStep(glm::vec2 const& t_ambientVelocity, glm::vec2 const& t_ambientAcceleartion, float t_time = 1)
            { applyMovementStep(glm::vec2(t_ambientVelocity), glm::vec2(t_ambientAcceleartion), t_time); }

        void applyTranslation(glm::vec2&& t_translation);

        glm::vec2 getMovementDirection()
            { return m_velocity + m_acceleration * 0.5f; }

        inline void setAssociatedModel(std::shared_ptr<glm::mat4> t_model)
            { m_model = t_model; }
        inline glm::vec2& acceleration()
            { return m_acceleration; }
        inline glm::vec2& velocity()
            { return m_velocity; }
        inline glm::vec2& lastTransformation()
            { return m_lastTransformation; }

        inline bool isStatic() const
            { return !m_dynamic; }
        inline bool isDynamic() const
            { return m_dynamic; }

        CollisionInfo checkCollision(Body2D& t_body, CollisionLevel t_collisionLevel);
        CollisionInfo checkInclusion(glm::vec2&& t_vertex);
        CollisionInfo checkBC(Body2D& t_body);
        CollisionInfo checkAABB(Body2D& t_body);
        CollisionInfo checkDetailed(Body2D& t_body);
        CollisionInfo checkEdge(glm::vec2& t_a, glm::vec2& t_b);
        // CollisionInfo checkEdgeInfluence(glm::vec2& t_center, float radius);
        // CollisionInfo checkEdgeInfluence();

    private:
        void calculateBindingCircle();
        void calculateAABBB();
        void calculateEdgeInfluence();

        std::shared_ptr<glm::mat4> m_model;

        glm::vec2 m_lastTransformation = glm::vec2(0);
        glm::vec2 m_acceleration = glm::vec2(0);
        glm::vec2 m_velocity = glm::vec2(0);

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