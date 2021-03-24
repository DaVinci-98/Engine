#pragma once

#include "EventSystem/eventEmitter.hpp"
#include "Glfw/Events/keyEvent.hpp"

namespace MyEngine::Glfw::Events
{
    /**
     * @brief Emits KeyEvent objects.
     * 
     */
    class KeyEventEmitter : public EventSystem::EventEmitter<KeyEvent>
    {
    public:
        /**
         * @brief Send a KeyEvent with provided:
         * 
         * @param t_keycode keyCode
         */
        inline void sendEvent(unsigned int t_keycode)
            { EventSystem::EventEmitter<KeyEvent>::sendEvent(KeyEvent(t_keycode)); }
        /**
         * @brief Send a KeyEvent with provided: 
         * 
         * @param t_mods - modificators present when the key was pressed.
         * @param t_key - key pressed.
         * @param t_keyEventType - was it a press/release/repeat action.
         */
        inline void sendEvent(KeyEvent::KeyMods& t_mods, KeyEvent::Key& t_key, KeyEvent::KeyEventType& t_keyEventType)
            { EventSystem::EventEmitter<KeyEvent>::sendEvent(KeyEvent(t_mods, t_key, t_keyEventType)); }
    };
}
