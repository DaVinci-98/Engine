#pragma once

#include "EventSystem/eventEmitter.hpp"
#include "Physics/Events/collisionEvent.hpp"

namespace MyEngine::Physics
{
    class CollisionEventEmitter : public EventSystem::EventEmitter<CollisionEvent>
    {
    public:
        inline void sendEvent(std::string& t_group, CollisionInfo& t_info,
            std::shared_ptr<Body2D> t_calling, std::shared_ptr<Body2D> t_second)
            { EventSystem::EventEmitter<CollisionEvent>::sendEvent(CollisionEvent(t_group, t_info, t_calling, t_second)); }
    };
}