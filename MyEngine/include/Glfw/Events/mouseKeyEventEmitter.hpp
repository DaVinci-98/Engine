#pragma once

#include "EventSystem/eventEmitter.hpp"
#include "Glfw/Events/mouseKeyEvent.hpp"

namespace MyEngine::Glfw::Events
{
    /**
     * @brief Emits MouseKeyEvent objects.
     * 
     */
    class MouseKeyEventEmitter: public EventSystem::EventEmitter<MouseKeyEvent>
    {
    public:
        /**
         * @brief Send a MouseKeyEvent with provided:
         * 
         * @param t_keycode keyCode
         * @param t_xPos mouse x coordinate
         * @param t_yPos mouse y coordinate
         */
        inline void sendEvent(unsigned int t_keycode, double t_xPos, double t_yPos)
            { EventSystem::EventEmitter<MouseKeyEvent>::sendEvent(MouseKeyEvent(t_keycode, t_xPos, t_yPos)); }
        /**
         * @brief Send a MouseKeyEvent with provided:
         * 
         * @param t_mods - modificators present when the key was pressed.
         * @param t_key - key pressed.
         * @param t_keyEventType - was it a press/release/repeat action.
         * @param t_xPos mouse x coordinate
         * @param t_yPos mouse y coordinate
         */
        inline void sendEvent(MouseKeyEvent::KeyMods& t_mods, MouseKeyEvent::Key& t_key, MouseKeyEvent::KeyEventType& t_keyEventType,
            double t_xPos, double t_yPos)
            { EventSystem::EventEmitter<MouseKeyEvent>::sendEvent(MouseKeyEvent(t_mods, t_key, t_keyEventType, t_xPos, t_yPos)); }
    };
}