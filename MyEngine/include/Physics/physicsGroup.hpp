#pragma once

#include "Physics/body2D.hpp"
#include "Physics/shared.hpp"
#include "Physics/Events/collisionEventEmitter.hpp"
#include "Helpers/smartVector.hpp"

#include <memory>
#include <vector>
#include <glm/glm.hpp>

namespace MyEngine::Physics
{
    class PhysicsGroup
    {
    public:
        PhysicsGroup(std::string& t_name, bool t_isStatic) : 
            m_name(t_name), m_isStatic(t_isStatic) { }

        void updateSpeed();
        void checkForCollisions();
        
        inline void setCollisionDetectionPipeline(std::vector<CollisionLevel>&& t_pipeline)
            { m_collisionDetectionPipeline = t_pipeline; }
        inline void addBody(std::shared_ptr<Body2D> t_body)
            { m_bodies.push_back(t_body); }
        void removeBody(std::shared_ptr<Body2D> t_body);

        inline glm::vec2& ambientVelocity()
            { return m_ambientVelocity; }
        inline glm::vec2& ambientAcceleration()
            { return m_ambientAcceleration; }
        inline CollisionEventEmitter& eventEmitter()
            { return m_emitter; }

    private:
        void takeMovementStep(float t_time);
        CollisionInfo runDetectionPipeline(Body2D& t_dynamicBody, Body2D& t_body);

        std::string m_name;
        bool m_isStatic;
        CollisionEventEmitter m_emitter;
        glm::vec2 m_ambientVelocity = glm::vec2(0);
        glm::vec2 m_ambientAcceleration = glm::vec2(0);
        std::vector<CollisionLevel> m_collisionDetectionPipeline;
        std::vector<std::shared_ptr<Body2D>> m_bodies;
    };
}