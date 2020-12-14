#pragma once

#include "Physics/body2D.hpp"
#include "Physics/physicsGroup.hpp"
#include "Physics/Events/collisionEventListener.hpp"
#include "shared.hpp"

#include <map>

namespace MyEngine::Physics
{
    class PhysicsManager
    {
        inline void update(float t_time = 1)
            { for(auto& [_, group] : m_groups) group.update(t_time); }

        inline void registerPhysicsGroup(std::string&& t_name);
        inline void unregisterPhysicsGroup(std::string&& t_name)
            { m_groups.erase(std::move(t_name)); }
        inline void registerCollisionCallback(std::string& t_name,
            std::function<void(CollisionEvent&)>&& t_callback,
            std::shared_ptr<Body2D>& t_body)
            { m_listners[t_name].registerCollisionCallback(std::move(t_callback), t_body); }
        
        inline PhysicsGroup& getGroup(std::string const& t_name)
            { return m_groups.find(t_name) -> second; }
        inline PhysicsGroup& getGroup(std::string&& t_name)
            { return m_groups.find(t_name) -> second;; }

    private:
        std::map<std::string, PhysicsGroup> m_groups;
        std::map<std::string, CollisionEventListener> m_listners;
    };
}