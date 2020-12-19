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
                if(bodyA -> isDynamic() && bodyA != bodyB)
                {
                    CollisionInfo info = runDetectionPipeline(*bodyA, *bodyB);
                    if(info.m_detected) m_emitter.sendEvent(m_name, info, bodyA, bodyB);
                }
                else if(bodyB -> isDynamic() && bodyA != bodyB)
                {
                    CollisionInfo info = runDetectionPipeline(*bodyB, *bodyA);
                    if(info.m_detected) m_emitter.sendEvent(m_name, info, bodyB, bodyA);
                }
            }
        }
    }

    CollisionInfo PhysicsGroup::runDetectionPipeline(Body2D& t_dynamicBody, Body2D& t_body)
    {
        for(auto& collisionLevel : m_collisionDetectionPipeline)
        {
            auto info = t_dynamicBody.checkCollision(t_body, collisionLevel);
            if(info.m_detected == false) return info;
        }

        return CollisionInfo { true };
    }

    void PhysicsGroup::takeMovementStep(float t_time)
    {
        for(auto& body : m_bodies)
            body -> applyMovementStep(m_ambientVelocity, m_ambientAcceleration, t_time);
    }
}