#pragma once

#include "EventSystem/eventListener.hpp"
#include "Glfw/Events/mouseMoveEvent.hpp"

#include <functional>

namespace MyEngine::Glfw::Events
{
    /**
     * @brief Listens for MouseMoveEvent objects through registered emitter.
     * 
     */
    class MouseMoveEventListener: public EventSystem::EventListener<MouseMoveEvent>
    {
    public:
        /**
         * @brief Sends the MouseMoveEvent to a callback registered under incrementing id.
         * 
         * @param t_mouseMoveEvent  rvalue reference to the to-be-sent MouseMoveEvent.
         */
        virtual void dispatch(MouseMoveEvent&& t_mouseMoveEvent) override;
        /**
         * @brief Registers a callback under incrementing id.
         * 
         * @param t_callback callback function, takes a reference to the MouseMoveEvent
         * @return unsigned int - id under which callback was registered
         */
        unsigned int registerMoveCallback(std::function<void(MouseMoveEvent&)>&& t_func);
    private:
        unsigned int m_lastId = 0;
    };
}