#pragma once

#include "EventSystem/eventListener.hpp"
#include "Glfw/Events/mouseKeyEvent.hpp"

namespace MyEngine::Glfw::Events
{
    class MouseKeyEventListener: public EventSystem::EventListener<MouseKeyEvent>
    {
    public:
        virtual void dispatch(MouseKeyEvent&& t_keyEvent) override;
        void registerKeyCallback(std::function<void(MouseKeyEvent&)>&& t_callback, unsigned int t_keycode);
        void registerKeyCallback(std::function<void(MouseKeyEvent&)>&& t_callback, 
            MouseKeyEvent::Key t_key, MouseKeyEvent::KeyMods t_mods, MouseKeyEvent::KeyEventType t_keyEventType);
    };
}