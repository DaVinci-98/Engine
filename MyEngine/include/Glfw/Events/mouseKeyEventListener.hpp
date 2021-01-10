#pragma once

#include "EventSystem/eventListener.hpp"
#include "Glfw/Events/mouseKeyEvent.hpp"

namespace MyEngine::Glfw::Events
{
    /**
     * @brief Listens for MouseKeyEvent objects through registered emitter.
     * 
     */
    class MouseKeyEventListener: public EventSystem::EventListener<MouseKeyEvent>
    {
    public:
        /**
         * @brief Sends the MouseKeyEvent to a callback registered with event's keycode.
         * 
         * @param t_keyEvent rvalue reference to the to-be-sent KeyEvent.
         */
        virtual void dispatch(MouseKeyEvent&& t_keyEvent) override;
        /**
         * @brief Register a callback for MouseKeyEvent under provided keyCode.
         * 
         * @param t_callback callback function, takes a reference to the MouseKeyEvent
         * @param t_keycode keyCode 
         */
        void registerKeyCallback(std::function<void(MouseKeyEvent&)>&& t_callback, unsigned int t_keycode);
        /**
         * @brief Send a MouseKeyEvent with provided: 
         * 
         * @param t_mods - modificators present when the key was pressed.
         * @param t_key - key pressed.
         * @param t_keyEventType - was it a press/release/repeat action.
         */
        void registerKeyCallback(std::function<void(MouseKeyEvent&)>&& t_callback, 
            MouseKeyEvent::Key t_key, MouseKeyEvent::KeyMods t_mods, MouseKeyEvent::KeyEventType t_keyEventType);
    };
}