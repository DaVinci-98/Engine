#include "Physics/physicsManager.hpp"

namespace MyEngine::Physics
{
    void PhysicsManager::update(float t_time)
    { 
        // m_bodies.removeLooseReferences();

        for(auto& [_, group] : m_groups)
            group.updateSpeed();

        for(auto& body : m_bodies)
            body->applyMovementStep(t_time);

        for(auto& [_, group] : m_groups)
            group.checkForCollisions();
    }

    void PhysicsManager::registerPhysicsGroup(std::string&& t_name, bool t_isStatic)
    { 
        m_groups.insert(std::pair<std::string, PhysicsGroup>(t_name, PhysicsGroup(t_name, t_isStatic))); 
        m_listners.insert(std::pair<std::string, CollisionEventListener>(t_name, CollisionEventListener()));

        m_listners[t_name].registerEmitter(getGroup(t_name).eventEmitter());

        // m_bodies.useCount()++;
    }

    void PhysicsManager::unregisterPhysicsGroup(std::string&& t_name)
    { 
        m_groups.erase(std::move(t_name));
        // m_bodies.useCount()--;
    }

    void PhysicsManager::addBody(std::string& t_group, std::shared_ptr<Body2D> t_body)
    { 
        m_bodies.pushBackUnique(t_body);
        getGroup(t_group).addBody(t_body);
    }

    void PhysicsManager::removeBody(std::shared_ptr<Body2D> t_body)
    {
        m_bodies.remove(t_body);
        for(auto& [_, group] : m_groups)
            group.removeBody(t_body);
    }
}