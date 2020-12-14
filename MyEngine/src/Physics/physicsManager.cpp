#include "Physics/physicsManager.hpp"

namespace MyEngine::Physics
{
    void PhysicsManager::registerPhysicsGroup(std::string&& t_name)
    { 
        m_groups.insert(std::pair<std::string, PhysicsGroup>(t_name, PhysicsGroup(t_name))); 
        m_listners.insert(std::pair<std::string, CollisionEventListener>(t_name, CollisionEventListener()));

        m_listners[t_name].registerEmitter(getGroup(t_name).eventEmitter());
    }
}