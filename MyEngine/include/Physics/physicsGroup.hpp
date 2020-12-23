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
        PhysicsGroup(std::string& t_name) : 
            m_name(t_name) { }

        void update(float t_time = 1);

        inline void setCollisionDetectionPipeline(std::vector<CollisionLevel>&& t_pipeline)
            { m_collisionDetectionPipeline = t_pipeline; }
        inline void setAmbientVelocity(glm::vec2&& t_velocity)
            { m_ambientVelocity = t_velocity; }
        inline void setAmbientAcceleration(glm::vec2&& t_acceleration)
            { m_ambientAcceleration = t_acceleration; }
        inline void addBody(std::shared_ptr<Body2D> t_body)
            { m_bodies.pushBack(t_body); }

        inline CollisionEventEmitter& eventEmitter()
            { return m_emitter; }

    private:
        void checkForCollisions();
        void takeMovementStep(float t_time);
        CollisionInfo runDetectionPipeline(Body2D& t_dynamicBody, Body2D& t_body);

        std::string m_name;

        CollisionEventEmitter m_emitter;

        glm::vec2 m_ambientVelocity = glm::vec2(0);
        glm::vec2 m_ambientAcceleration = glm::vec2(0);
        std::vector<CollisionLevel> m_collisionDetectionPipeline;
        Helpers::SmartVector<Body2D> m_bodies;
    };
}