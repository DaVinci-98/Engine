#include "Physics/physicsGroup.hpp"
#include "Physics/Events/collisionEvent.hpp"

namespace MyEngine::Physics
{
    void PhysicsGroup::update(float t_time)
    {
        m_bodies.removeLooseReferences();

        takeMovementStep(t_time);
        checkForCollisions();
    }

    void PhysicsGroup::checkForCollisions()
    {
        for(auto& bodyA : m_bodies)
        {
            for(auto& bodyB : m_bodies)
            {
                if(bodyA -> isDynamic())
                {
                    CollisionInfo info = runDetectionPipeline(*bodyA, *bodyB);
                    m_emitter.sendEvent(m_name, info, bodyA, bodyB);
                }
                else if(bodyB -> isDynamic())
                {
                    CollisionInfo info = runDetectionPipeline(*bodyB, *bodyA);
                    m_emitter.sendEvent(m_name, info, bodyB, bodyA);
                }
            }
        }
    }

    CollisionInfo PhysicsGroup::runDetectionPipeline(Body2D& t_dynamicBody, Body2D& t_body)
    {
        for(auto& collisionLevel : m_collisionDetectionPipeline)
        {
            auto info = t_dynamicBody.checkCollision(t_body, collisionLevel);
            if(info.m_detected == true) return info;
        }

        return CollisionInfo { false };
    }

    void PhysicsGroup::takeMovementStep(float t_time)
    {
        for(auto& body : m_bodies)
            body -> applyMovementStep(m_ambientVelocity, m_ambientAcceleration, t_time);
    }
}