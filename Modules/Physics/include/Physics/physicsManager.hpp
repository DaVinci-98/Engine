#pragma once

#include "Physics/body2D.hpp"
#include "Physics/physicsGroup.hpp"
#include "shared.hpp"

#include <map>
#include <vector>

namespace MyEngine::Physics
{
    /**
     * @brief Used to manage physics groups and listener/emitter objects for CollisionEvents.
     * 
     */
    class PhysicsManager
    {
    public:
        /**
         * @brief Move physics provided number of seconds forward in time.
         * 
         * @param t_time number of seconds physics should be moved by.
         */
        void update(float t_time = 1);
        /**
         * @brief Create a physics group within this manager.
         * 
         * @param t_name name of the physics group.
         * @param t_isStatic if true, the colisions between dynamic objects won't be checked.
         */
        void registerPhysicsGroup(std::string&& t_name, bool t_isStatic);
        /**
         * @brief Remove a physics group from this manager.
         * 
         * @param t_name name of the physics group.
         */
        void unregisterPhysicsGroup(std::string&& t_name);
        /**
         * @brief Add a body to specified physics group.
         * 
         * @param t_name name of the physics group.
         * @param t_body shared pointer to added body.
         */
        void addBody(std::string& t_group, std::shared_ptr<Body2D> t_body);
        /**
         * @brief Remove a body from physics manager.
         * 
         * @param t_body shared pointer to removed body.
         */
        void removeBody(std::shared_ptr<Body2D> t_body);

        /**
         * @brief Create a physics group within this manager.
         * 
         * @param t_name name of the physics group.
         * @param t_isStatic if true, the colisions between dynamic objects won't be checked.
         */
        inline void registerPhysicsGroup(std::string const& t_name, bool t_isStatic)
            { registerPhysicsGroup(std::string(t_name), t_isStatic); }

        void registerCollisionCallback(
            std::string& t_name,
            std::function<void(CollisionInfo&, std::shared_ptr<Body2D>, std::shared_ptr<Body2D>)>&& t_callback,
            std::shared_ptr<Body2D> t_body);

        /**
         * @brief Get a reference to a PhysicsGroup object with provided name.
         * 
         */
        inline PhysicsGroup& getGroup(std::string const& t_name)
            { return m_groups.find(t_name) -> second; }
        /**
         * @brief Get a reference to a PhysicsGroup object with provided name.
         * 
         */
        inline PhysicsGroup& getGroup(std::string&& t_name)
            { return m_groups.find(t_name) -> second; }

    private:
        std::map<std::string, PhysicsGroup> m_groups;
        std::vector<std::shared_ptr<Body2D>> m_bodies;
    };
}