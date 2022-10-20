#pragma once

#include "Physics/body2D.hpp"
#include "Physics/shared.hpp"

#include <memory>
#include <vector>
#include <glm/glm.hpp>
#include <set>
#include <map>
#include <functional>

namespace MyEngine::Physics
{
    /**
     * @brief Groups physics object that are supposed to interact with each other, 
     * or should have a common acceleration/velocity applied to them.
     * 
     */
    class PhysicsGroup
    {
    public:
        /**
         * @brief Construct a new PhysicsGroup object.
         * 
         * @param t_name name of the physics group.
         * @param t_isStatic if true, the colisions between dynamic objects won't be checked.
         */
        PhysicsGroup(std::string& t_name, bool t_isStatic) : 
            m_name(t_name), m_isStatic(t_isStatic) { }

        /**
         * @brief Update velocity/acceleration of bodies assigned to this group.
         * 
         */
        void updateSpeed();
        /**
         * @brief Check for collisions between bodies in group using collision detection pipeline,
         * set using setCollisionDetectionPipeline() function.
         * 
         */
        void checkForCollisions();
        
        /**
         * @brief Set the collision detection pipeline used in checkForCollisions() function.
         * 
         * @param t_pipeline rvalue reference to the pipeline set.
         */
        inline void setCollisionDetectionPipeline(std::vector<CollisionLevel>&& t_pipeline)
            { m_collisionDetectionPipeline = t_pipeline; }
        /**
         * @brief Add a body to this physics group.
         * 
         * @param t_body shared pointer to added body.
         */
        inline void addBody(std::shared_ptr<Body2D> t_body)
            { m_bodies.insert(t_body); }
        /**
         * @brief Remove a body from this physics group.
         * 
         * @param t_body shared pointer to added body.
         */
        void removeBody(std::shared_ptr<Body2D> t_body);

        /**
         * @brief Velocity applied to the bodies in this physics group,
         * used in updateSpeed().
         * 
         * @return Reference to glm::vec2 describing velocity.
         */
        inline glm::vec2& ambientVelocity()
            { return m_ambientVelocity; }
        /**
         * @brief Acceleration applied to the bodies in this physics group,
         * used in updateSpeed().
         * 
         * @return Reference to glm::vec2 describing acceleration.
         */
        inline glm::vec2& ambientAcceleration()
            { return m_ambientAcceleration; }

        void registerCollisionCallback(
            std::function<void(CollisionInfo&, std::shared_ptr<Body2D>, std::shared_ptr<Body2D>)>&& t_callback,
            std::shared_ptr<Body2D> t_body);

    private:
        void takeMovementStep(float t_time);
        CollisionInfo runDetectionPipeline(std::shared_ptr<Body2D> t_dynamicBody, std::shared_ptr<Body2D> t_body);

        std::string m_name;
        bool m_isStatic;
        glm::vec2 m_ambientVelocity = glm::vec2(0);
        glm::vec2 m_ambientAcceleration = glm::vec2(0);
        std::vector<CollisionLevel> m_collisionDetectionPipeline;
        std::set<std::shared_ptr<Body2D>> m_bodies;
        std::map<std::shared_ptr<Body2D>, std::function<void(CollisionInfo&, std::shared_ptr<Body2D>, std::shared_ptr<Body2D>)>> m_callbackMap;
    };
}