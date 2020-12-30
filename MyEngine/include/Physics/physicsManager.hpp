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
    public:
        void update(float t_time = 1);
        void registerPhysicsGroup(std::string&& t_name, bool t_isStatic);
        void unregisterPhysicsGroup(std::string&& t_name);
        void addBody(std::string& t_group, std::shared_ptr<Body2D> t_body);

        inline void registerPhysicsGroup(std::string const& t_name, bool t_isStatic)
            { registerPhysicsGroup(std::string(t_name), t_isStatic); }
        inline void registerCollisionCallback(std::string& t_name,
            std::function<void(CollisionEvent&)>&& t_callback,
            std::shared_ptr<Body2D> t_body)
            { m_listners[t_name].registerCollisionCallback(std::move(t_callback), t_body); }
        
        inline PhysicsGroup& getGroup(std::string const& t_name)
            { return m_groups.find(t_name) -> second; }
        inline PhysicsGroup& getGroup(std::string&& t_name)
            { return m_groups.find(t_name) -> second; }

    private:
        std::map<std::string, PhysicsGroup> m_groups;
        std::map<std::string, CollisionEventListener> m_listners;
        Helpers::SmartVector<Body2D> m_bodies;
    };
}