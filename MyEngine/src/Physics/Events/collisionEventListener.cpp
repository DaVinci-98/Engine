#include "Physics/Events/collisionEventListener.hpp"

namespace MyEngine::Physics
{
    void CollisionEventListener::dispatch(CollisionEvent&& t_collisionEvent)
    {
        if(m_bodyIds.count(t_collisionEvent.dynamicBody()) == 1)
        {
            auto id = m_bodyIds[t_collisionEvent.dynamicBody()];
            callback(id)(t_collisionEvent);
        }

        if(m_bodyIds.count(t_collisionEvent.staticBody()) == 1)
        {
            auto id = m_bodyIds[t_collisionEvent.staticBody()];
            callback(id)(t_collisionEvent);
        }

        if(!t_collisionEvent.isHandled() && nextDispatcher())
        {
            nextDispatcher()(std::move(t_collisionEvent));
        }
    }

    void CollisionEventListener::registerCollisionCallback(
        std::function<void(CollisionEvent&)>&& t_callback,
        std::shared_ptr<Body2D>& t_body)
    {
        unsigned int id = m_lastRegistered++;
        m_bodyIds.insert(std::make_pair(t_body, id));
        registerCallback(id, std::move(t_callback));
    }
}