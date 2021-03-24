#pragma once

#include "EventSystem/event.hpp"
#include "Physics/body2D.hpp"

#include <memory>
#include <tuple>
#include <glm/glm.hpp>

namespace MyEngine::Physics::Events
{
    /**
     * @brief Event for sending information about detected collisions.
     * 
     */
    class CollisionEvent : public EventSystem::Event<CollisionEvent>
    {
    public:
        /**
         * @brief Construct a new Collision Event object.
         * 
         * @param t_group physics group in which collision was detected.
         * @param t_info CollisionInfo object storing variety of information about the collision.
         * @param t_calling body which was registered for collision detection.
         * @param t_second body which collided with the calling body.
         */
        CollisionEvent(std::string& t_group, CollisionInfo& t_info,
            std::shared_ptr<Body2D> t_calling, std::shared_ptr<Body2D> t_second) :
            m_physicsGroup(t_group), m_callingBody(t_calling), m_secondBody(t_second),  m_info(t_info) { }
        
        /**
         * @brief Get physics group in which collision was detected.
         * 
         */
        inline std::string group()
            { return m_physicsGroup; }
        /**
         * @brief Get body which was registered for collision detection.
         * 
         */
        inline std::shared_ptr<Body2D> callingBody()
            { return m_callingBody; }
        /**
         * @brief Get body which collided with the calling body.
         * 
         */
        inline std::shared_ptr<Body2D> secondBody()
            { return m_secondBody; }
        /**
         * @brief Get an object storing variety of information about the collision.
         * 
         * @return Reference to CollisionInfo object.
         */
        inline CollisionInfo& info()
            { return m_info; }

    private:
        CollisionInfo m_info;
        std::string m_physicsGroup;
        std::shared_ptr<Body2D> m_callingBody;
        std::shared_ptr<Body2D> m_secondBody;
    };
}