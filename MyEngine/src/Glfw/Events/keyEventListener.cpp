#include "Glfw/Events/keyEventListener.hpp"

namespace MyEngine::Glfw::Events
{
    void KeyEventListener::dispatch(KeyEvent&& t_keyEvent)
    {
        unsigned int keyCode = t_keyEvent.keyCode();
        if(callback(keyCode))
        {
            callback(keyCode)(t_keyEvent);
        }

        if(!t_keyEvent.isHandled() && nextDispatcher())
        {
            nextDispatcher()(std::move(t_keyEvent));
        }
    }

    void KeyEventListener::registerKeyCallback(std::function<void(KeyEvent&)>&& t_callback, 
        KeyEvent::Key t_key, KeyEvent::KeyMods t_mods, KeyEvent::KeyEventType t_keyEventType)
    {
        unsigned int keyCode = KeyEvent::getKeyCode(t_mods, t_key, t_keyEventType);
        registerCallback(keyCode, std::move(t_callback));
    }

    void KeyEventListener::registerKeyCallback(std::function<void(KeyEvent&)>&& t_callback, unsigned int t_keycode)
    {
        registerCallback(t_keycode, std::move(t_callback));
    }
}