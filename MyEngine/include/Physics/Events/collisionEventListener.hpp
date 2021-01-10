#pragma once

#include "EventSystem/eventListener.hpp"
#include "Physics/Events/collisionEvent.hpp"

#include <map>

namespace MyEngine::Physics::Events
{
    /**
     * @brief Listens for CollisionEvent objects through registered emitter.
     * 
     */
    class CollisionEventListener : public EventSystem::EventListener<CollisionEvent>
    {
    public:
        /**
         * @brief Sends the CollisionEvent to a callback registered for event's calling body.
         * 
         * @param t_collisionEvent rvalue reference to the to-be-sent CollisionEvent.
         */
        virtual void dispatch(CollisionEvent&& t_collisionEvent) override;
        /**
         * @brief Register a callback for CollisionEvent for provided body.
         * 
         * @param t_callback callback function, takes a reference to the KeyEvent
         * @param t_body pointer to body, 
         * which will triger the callback when coliding with another body
         */
        void registerCollisionCallback(
            std::function<void(CollisionEvent&)>&& t_callback,
            std::shared_ptr<Body2D> t_body);
    
    private:
        unsigned int m_lastRegistered = 0;
        std::map<std::shared_ptr<Body2D>, unsigned int> m_bodyIds;
    };
}