#pragma once

#include "EventSystem/eventEmitter.hpp"
#include "Glfw/Events/windowEvent.hpp"

namespace MyEngine::Glfw::Events
{
    /**
     * @brief Emits WindowEvent objects.
     * 
     */
    class WindowEventEmitter: public EventSystem::EventEmitter<WindowEvent>
    {
    public:
        /**
         * @brief Send WindowEvent of WindowEventType::RESIZE
         * 
         * @param t_oldWidth window width before change
         * @param t_oldHeight window height before change 
         * @param t_newWidth window width after change
         * @param t_newHeight window height after change
         */
        inline void sendEvent(int t_oldWidth, int t_oldHeight, int t_newWidth, int t_newHeight)
            { EventSystem::EventEmitter<WindowEvent>::sendEvent(WindowEvent(t_oldWidth, t_oldHeight, t_newWidth, t_newHeight)); }
    };
}