#pragma once

#include "EventSystem/event.hpp"
#include "EventSystem/eventEmitter.hpp"
#include "Renderer/drawable2D.hpp"
#include "Renderer/Events/drawableAddEvent.hpp"

#include <functional>
#include <memory>

namespace MyEngine::Renderer::Events
{
    /**
     * @brief Emits DrawableAddEvent objects.
     * 
     */
    class DrawableAddEventEmitter: public EventSystem::EventEmitter<DrawableAddEvent>
    {
    public:
        /**
         * @brief Send a DrawableAddEvent with provided:
         * 
         * @param t_drawable Object which will be drawn.
         * @param t_callback Function to call before drawing the object.
         */
        inline void sendEvent(std::shared_ptr<Drawable2D> &t_drawable, std::function<void(void)>&& t_callback)
            { EventSystem::EventEmitter<DrawableAddEvent>::sendEvent(DrawableAddEvent(t_drawable, std::move(t_callback))); }
    };
}