#pragma once

#include <glm/glm.hpp>
#include <vector>

namespace MyEngine::Physics
{
    enum CollisionLevel
    {
        CIRCLE_BOUND,
        AXIS_ALLIGNED_BOUNDING_BOX,
        // EDGE_INFLUENCE_ZONE,
        EDGE_COLLISION
    };

    struct CollisionInfo
    {
        bool m_detected;
        // glm::vec2 m_penDirection;
        // std::vector<std::tuple<glm::vec2, glm::vec2>> m_edges;    
    };
}