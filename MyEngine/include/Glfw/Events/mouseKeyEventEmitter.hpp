#pragma once

#include "EventSystem/eventEmitter.hpp"
#include "Glfw/Events/mouseKeyEvent.hpp"

namespace MyEngine::Glfw::Events
{
    class MouseKeyEventEmitter: public EventSystem::EventEmitter<MouseKeyEvent>
    {
    public:
        inline void sendEvent(unsigned int t_keycode, double t_xPos, double t_yPos)
            { EventSystem::EventEmitter<MouseKeyEvent>::sendEvent(MouseKeyEvent(t_keycode, t_xPos, t_yPos)); }
        inline void sendEvent(MouseKeyEvent::KeyMods& t_mods, MouseKeyEvent::Key& t_key, MouseKeyEvent::KeyEventType& t_keyEventType,
            double t_xPos, double t_yPos)
            { EventSystem::EventEmitter<MouseKeyEvent>::sendEvent(MouseKeyEvent(t_mods, t_key, t_keyEventType, t_xPos, t_yPos)); }
    };
}