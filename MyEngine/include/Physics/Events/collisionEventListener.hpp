#pragma once

#include "EventSystem/eventListener.hpp"
#include "Physics/Events/collisionEvent.hpp"

#include <map>

namespace MyEngine::Physics
{
    class CollisionEventListener : public EventSystem::EventListener<CollisionEvent>
    {
    public:
        virtual void dispatch(CollisionEvent&& t_collisionEvent) override;
        void registerCollisionCallback(
            std::function<void(CollisionEvent&)>&& t_callback,
            std::shared_ptr<Body2D>& t_body);
    
    private:
        unsigned int m_lastRegistered = 0;
        std::map<std::shared_ptr<Body2D>, unsigned int> m_bodyIds;
    };
}