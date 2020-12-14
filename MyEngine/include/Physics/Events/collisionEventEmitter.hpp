#pragma once

#include "EventSystem/eventEmitter.hpp"
#include "Physics/Events/collisionEvent.hpp"

namespace MyEngine::Physics
{
    class CollisionEventEmitter : public EventSystem::EventEmitter<CollisionEvent>
    {
    public:
        inline void sendEvent(std::string& t_group, CollisionInfo t_info,
            std::shared_ptr<Body2D> t_dynamic, std::shared_ptr<Body2D> t_static)
            { EventSystem::EventEmitter<CollisionEvent>::sendEvent(CollisionEvent(t_group, t_info, t_dynamic, t_static)); }
    };
}