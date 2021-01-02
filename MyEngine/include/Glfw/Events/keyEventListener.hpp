#pragma once

#include "Glfw/Events/keyEvent.hpp"
#include "EventSystem/eventListener.hpp"

#include <unordered_map>
#include <functional>

namespace MyEngine::Glfw::Events
{
    /**
     * @brief Listens for KeyEvent obejcts through registered emitter.
     * 
     */
    class KeyEventListener: public EventSystem::EventListener<KeyEvent>
    {
    public:
        /**
         * @brief Sends the KeyEvent to a callback registered with event's keycode.
         * 
         * @param t_keyEvent rvalue reference to the to-be-sent KeyEvent.
         */
        virtual void dispatch(KeyEvent&& t_keyEvent) override;
        /**
         * @brief Register a callback for KeyEvent under provided keyCode.
         * 
         * @param t_callback callback function, takes a reference to the KeyEvent
         * @param t_keycode keyCode 
         */
        void registerKeyCallback(std::function<void(KeyEvent&)>&& t_callback, unsigned int t_keycode);
        /**
         * @brief Registere a callback for KeyEvent.
         * 
         * @param t_callback callback function, takes a reference to the KeyEvent
         * @param t_mods modificators present when the key was pressed.
         * @param t_key key pressed.
         * @param t_keyEventType was it a press/release/repeat action.
         */
        void registerKeyCallback(std::function<void(KeyEvent&)>&& t_callback, 
            KeyEvent::Key t_key, KeyEvent::KeyMods t_mods, KeyEvent::KeyEventType t_keyEventType);
    };
} 
