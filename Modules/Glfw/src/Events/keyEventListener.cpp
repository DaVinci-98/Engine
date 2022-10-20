#include "Glfw/Events/keyEventListener.hpp"
#include "Logger/logger.hpp"
#include "EventSystem/event.hpp"

namespace MyEngine::Glfw::Events
{
    void KeyEventListener::dispatch(KeyEvent&& t_event)
    {
        unsigned int keyCode = t_event.keyCode();
        if(callback(keyCode))
        {
            t_event.dispatched();
            callback(keyCode)(t_event);
        }

        if(!t_event.isHandled() && nextDispatcher())
        {
            nextDispatcher()(std::move(t_event));
        }

        if(!t_event.isHandled() && t_event.isDispatched())
        {
            Logger::Logger::log<EventSystem::Event<KeyEvent>>() -> warn(
                "[Unhandled]"); 
        }
    }

    void KeyEventListener::registerKeyCallback(std::function<void(KeyEvent&)>&& t_callback, 
        KeyEvent::Key t_key, KeyEvent::KeyMods t_mods, KeyEvent::KeyEventType t_keyEventType)
    {
        Logger::Logger::log<EventSystem::Event<KeyEvent>>() -> info(
            "[Registered] [Callback] [Key]: {0}, {1}, {2}",
            static_cast<unsigned int>(t_key), static_cast<unsigned int>(t_mods), static_cast<unsigned int>(t_keyEventType));
        unsigned int keyCode = KeyEvent::getKeyCode(t_mods, t_key, t_keyEventType);
        registerCallback(keyCode, std::move(t_callback));
    }

    void KeyEventListener::registerKeyCallback(std::function<void(KeyEvent&)>&& t_callback, unsigned int t_keycode)
    {
        Logger::Logger::log<EventSystem::Event<KeyEvent>>() -> info(
            "[Registered] [Callback] [Keycode]: {0}",
            t_keycode);
        registerCallback(t_keycode, std::move(t_callback));
    }
}