#pragma once

#include "EventSystem/eventListener.hpp"
#include "Glfw/Events/windowEvent.hpp"

namespace MyEngine::Glfw::Events
{
    /**
     * @brief Listens for WindowEvent objects through registered emitter.
     * 
     */
    class WindowEventListener: public EventSystem::EventListener<WindowEvent>
    {
    public:
        /**
         * @brief Sends the WindowEvent to a callback registered under WindowEventType.
         * 
         * @param t_windowEvent  rvalue reference to the to-be-sent WindowEvent.
         */
        virtual void dispatch(WindowEvent&& t_windowEvent) override;
        /**
         * @brief Registers a callback under WindowEventType::RESIZE.
         * 
         * @param t_callback callback function, takes a reference to the WindowEvent
         */
        void registerResizeCallback(std::function<void(WindowEvent&)>&& t_callback);
    };
}