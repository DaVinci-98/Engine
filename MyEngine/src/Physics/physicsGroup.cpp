#include "Physics/physicsGroup.hpp"
#include "Physics/Events/collisionEvent.hpp"

namespace MyEngine::Physics
{
    void PhysicsGroup::updateSpeed()
    {
        for(auto& body : m_bodies)
        {
            body -> addGroupAcceleration(m_ambientAcceleration);
            body -> addGroupVelocity(m_ambientVelocity);
        }
    }

    void PhysicsGroup::removeBody(std::shared_ptr<Body2D> t_body)
    { 
        auto iterator = std::find(m_bodies.begin(), m_bodies.end(), t_body); 
        if(iterator != m_bodies.end())
            m_bodies.erase(iterator);
    }

    void PhysicsGroup::checkForCollisions()
    {
        for(auto& bodyA : m_bodies)
        {
            for(auto& bodyB : m_bodies)
            {
                if(m_isStatic)
                {
                    if(bodyA -> isDynamic() && bodyB -> isStatic() && bodyA != bodyB)
                    {
                        CollisionInfo info = runDetectionPipeline(*bodyA, *bodyB);
                        if(info.m_detected) m_emitter.sendEvent(m_name, info, bodyA, bodyB);
                    }
                    else if(bodyB -> isDynamic() && bodyA ->isStatic() && bodyA != bodyB)
                    {
                        CollisionInfo info = runDetectionPipeline(*bodyB, *bodyA);
                        if(info.m_detected) m_emitter.sendEvent(m_name, info, bodyB, bodyA);
                    }
                }
                else
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
    }

    CollisionInfo PhysicsGroup::runDetectionPipeline(Body2D& t_dynamicBody, Body2D& t_body)
    {
        CollisionInfo info;
        for(auto& collisionLevel : m_collisionDetectionPipeline)
        {
            info = t_dynamicBody.checkCollision(t_body, collisionLevel);
            if(info.m_detected == false) return info;
        }

        return info;
    }
}