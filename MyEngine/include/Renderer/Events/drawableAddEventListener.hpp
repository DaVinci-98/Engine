#pragma once

#include "EventSystem/event.hpp"
#include "EventSystem/eventListener.hpp"

#include "Renderer/Events/drawableAddEvent.hpp"
#include <vector>

namespace MyEngine::Renderer::Events
{
    /**
     * @brief Listens for and collects DrawableAddEvents.
     * 
     */
    class DrawableAddEventListener: public EventSystem::EventListener<DrawableAddEvent>
    {
    public:
        /**
         * @brief Collects DrawableAddEvents.
         * 
         * @param t_collisionEvent rvalue reference to the DrawableAddEvent.
         */
        void dispatch(DrawableAddEvent&& t_event) override;

        /**
         * @brief Gets and underlying vector with DrawableAddEvents.
         * 
         */
        inline std::vector<DrawableAddEvent>&& drawableAddEvents()
            { return std::move(m_events); }
            
    private:
        std::vector<DrawableAddEvent> m_events;
    };
}