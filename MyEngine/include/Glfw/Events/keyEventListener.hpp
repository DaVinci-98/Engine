#pragma once

#include "Glfw/Events/keyEvent.hpp"
#include "EventSystem/eventListener.hpp"

#include <unordered_map>
#include <functional>

namespace MyEngine::Glfw::Events
{
    class KeyEventListener: public EventSystem::EventListener<KeyEvent>
    {
    public:
        virtual void dispatch(KeyEvent&& t_keyEvent) override;
        void registerKeyCallback(std::function<void(KeyEvent&)>&& t_callback, unsigned int t_keycode);
        void registerKeyCallback(std::function<void(KeyEvent&)>&& t_callback, 
            KeyEvent::Key t_key, KeyEvent::KeyMods t_mods, KeyEvent::KeyEventType t_keyEventType);
    };
} 
