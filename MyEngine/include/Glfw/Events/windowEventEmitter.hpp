#pragma once

#include "EventSystem/eventEmitter.hpp"
#include "Glfw/Events/windowEvent.hpp"

namespace MyEngine::Glfw::Events
{
    class WindowEventEmitter: public EventSystem::EventEmitter<WindowEvent>
    {
    public:
        inline void sendEvent(WindowEvent::WindowEventType t_type, 
            int t_oldWidth, int t_oldHeight, int t_newWidth, int t_newHeight)
            { EventSystem::EventEmitter<WindowEvent>::sendEvent(WindowEvent(t_type, t_oldWidth, t_oldHeight, t_newWidth, t_newHeight)); }
    };
}