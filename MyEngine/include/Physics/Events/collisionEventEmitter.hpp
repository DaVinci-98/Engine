#pragma once

#include "EventSystem/eventEmitter.hpp"
#include "Physics/Events/collisionEvent.hpp"

namespace MyEngine::Physics
{
    /**
     * @brief Emits CollisionEvent obejcts.
     * 
     */
    class CollisionEventEmitter : public EventSystem::EventEmitter<CollisionEvent>
    {
    public:
        /**
         * @brief Send a KeyEvent with provided:
         * 
         * @param t_group physics group in which collision was detected.
         * @param t_info CollisionInfo object storing variety of information about the collision.
         * @param t_calling body which was registered for collision detection.
         * @param t_second body which colided with the calling body.
         */
        inline void sendEvent(std::string& t_group, CollisionInfo& t_info,
            std::shared_ptr<Body2D> t_calling, std::shared_ptr<Body2D> t_second)
            { EventSystem::EventEmitter<CollisionEvent>::sendEvent(CollisionEvent(t_group, t_info, t_calling, t_second)); }
    };
}