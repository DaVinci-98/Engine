#include "Physics/physicsManager.hpp"

namespace MyEngine::Physics
{
    void PhysicsManager::update(float t_time)
    { 
        // m_bodies.removeLooseReferences();

        for(auto& [_, group] : m_groups)
            group.updateSpeed();

        for(auto& body : m_bodies)
            body -> applyMovementStep(t_time);

        for(auto& [_, group] : m_groups)
            group.checkForCollisions();
    }

    void PhysicsManager::registerPhysicsGroup(std::string&& t_name, bool t_isStatic)
    { 
        m_groups.insert(std::pair<std::string, PhysicsGroup>(t_name, PhysicsGroup(t_name, t_isStatic)));
    }

    void PhysicsManager::unregisterPhysicsGroup(std::string&& t_name)
    { 
        m_groups.erase(std::move(t_name));
        // m_bodies.useCount()--;
    }

    void PhysicsManager::addBody(std::string& t_group, std::shared_ptr<Body2D> t_body)
    { 
        auto iterator = std::find(m_bodies.begin(), m_bodies.end(), t_body); 
        if(iterator == m_bodies.end())    
            m_bodies.push_back(t_body);
        getGroup(t_group).addBody(t_body);
    }

    void PhysicsManager::removeBody(std::shared_ptr<Body2D> t_body)
    {
        auto iterator = std::find(m_bodies.begin(), m_bodies.end(), t_body); 
        if(iterator != m_bodies.end())    
            m_bodies.erase(iterator);
        for(auto& [_, group] : m_groups)
            group.removeBody(t_body);
    }

    void PhysicsManager::registerCollisionCallback(
        std::string& t_name,
        std::function<void(CollisionInfo&, std::shared_ptr<Body2D>, std::shared_ptr<Body2D>)>&& t_callback,
        std::shared_ptr<Body2D> t_body)
    {
        getGroup(t_name).registerCollisionCallback(std::move(t_callback), t_body);
    }
}