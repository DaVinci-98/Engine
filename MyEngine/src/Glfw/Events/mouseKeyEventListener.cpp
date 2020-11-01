#include "Glfw/Events/mouseKeyEventListener.hpp"

namespace MyEngine::Glfw::Events
{
    void MouseKeyEventListener::dispatch(MouseKeyEvent&& t_keyEvent)
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

    void MouseKeyEventListener::registerKeyCallback(std::function<void(MouseKeyEvent&)>&& t_callback, 
        MouseKeyEvent::Key t_key, MouseKeyEvent::KeyMods t_mods, MouseKeyEvent::KeyEventType t_keyEventType)
    {
        unsigned int keyCode = MouseKeyEvent::getKeyCode(t_mods, t_key, t_keyEventType);
        registerCallback(keyCode, std::move(t_callback));
    }

    void MouseKeyEventListener::registerKeyCallback(std::function<void(MouseKeyEvent&)>&& t_callback, unsigned int t_keycode)
    {
        registerCallback(t_keycode, std::move(t_callback));
    }
}