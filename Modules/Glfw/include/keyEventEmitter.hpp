#pragma once

#include "eventEmitter.hpp"
#include "keyEvent.hpp"

namespace MyEngine::Glfw
{
    class KeyEventEmitter : public EventSystem::EventEmitter<KeyEvent>
    {
    public:
        inline void sendEvent(unsigned int t_keycode)
            { EventSystem::EventEmitter<KeyEvent>::sendEvent(KeyEvent(t_keycode)); }
        inline void sendEvent(KeyEvent::KeyMods& t_mods, KeyEvent::Key& t_key, KeyEvent::KeyEventType& t_keyEventType)
            { EventSystem::EventEmitter<KeyEvent>::sendEvent(KeyEvent(t_mods, t_key, t_keyEventType)); }
    };
}
