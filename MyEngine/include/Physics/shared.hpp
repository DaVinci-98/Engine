#pragma once

#include <glm/glm.hpp>
#include <vector>

namespace MyEngine::Physics
{
    enum CollisionLevel
    {
        CIRCLE_BOUND,
        AXIS_ALLIGNED_BOUNDING_BOX,
        OUT_OF_BOUNDS,
        // EDGE_INFLUENCE_ZONE,
        EDGE_COLLISION
    };

    struct CollisionInfo
    {
        bool m_detected;
        std::vector<glm::vec2> m_collisionPoints;
        std::vector<glm::vec2> m_simplex;
        glm::vec2 m_collisionCenter;
        glm::vec2 m_direction;
        glm::vec2 m_penetration;
        // std::vector<std::tuple<glm::vec2, glm::vec2>> m_edges;    
    };
}