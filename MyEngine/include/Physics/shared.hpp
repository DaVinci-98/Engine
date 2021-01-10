#pragma once

#include <glm/glm.hpp>
#include <vector>

namespace MyEngine::Physics
{
    /**
     * @brief Collision detection algorithms which can be put in collision detection pipeline.
     * 
     */
    enum CollisionLevel
    {
        CIRCLE_BOUND,
        AXIS_ALIGNED_BOUNDING_BOX,
        OUT_OF_BOUNDS,
        // EDGE_INFLUENCE_ZONE,
        EDGE_COLLISION
    };

    /**
     * @brief Information about the collision,
     * only the m_detected field is guaranteed to be filled in,
     * the rest depends on algorithm used.
     * 
     */
    struct CollisionInfo
    {
        bool m_detected;
        std::vector<glm::vec2> m_collisionPoints;
        glm::vec2 m_direction;
        glm::vec2 m_penetration;
        // std::vector<std::tuple<glm::vec2, glm::vec2>> m_edges;    
    };
}