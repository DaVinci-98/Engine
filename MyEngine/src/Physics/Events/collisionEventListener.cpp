#include "Physics/Events/collisionEventListener.hpp"
#include "Helpers/logger.hpp"
#include "EventSystem/event.hpp"

namespace MyEngine::Physics::Events
{
    void CollisionEventListener::dispatch(CollisionEvent&& t_collisionEvent)
    {
        if(m_bodyIds.count(t_collisionEvent.callingBody()) == 1)
        {
            t_collisionEvent.dispatched();
            auto id = m_bodyIds[t_collisionEvent.callingBody()];
            callback(id)(t_collisionEvent);
        }

        if(!t_collisionEvent.isHandled() && nextDispatcher())
        {
            nextDispatcher()(std::move(t_collisionEvent));
        }

        if(!t_collisionEvent.isHandled() && t_collisionEvent.isDispatched())
        {
            Helpers::Logger::log<EventSystem::Event<CollisionEvent>>() -> warn("[Unhandled]"); 
        }
    }

    void CollisionEventListener::registerCollisionCallback(
        std::function<void(CollisionEvent&)>&& t_callback,
        std::shared_ptr<Body2D> t_body)
    {
        unsigned int id = m_lastRegistered++;
        m_bodyIds.insert(std::make_pair(t_body, id));
        registerCallback(id, std::move(t_callback));
    }
}