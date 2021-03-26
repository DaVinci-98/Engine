#include "Glfw/Events/windowEventListener.hpp"
#include "Helpers/logger.hpp"
#include "EventSystem/event.hpp"

namespace MyEngine::Glfw::Events
{
    void WindowEventListener::dispatch(WindowEvent&& t_windowEvent)
    {
        WindowEvent::WindowEventType type = t_windowEvent.eventType();
        if(callback(type))
        {
            t_windowEvent.dispatched();
            callback(type)(t_windowEvent);
        }

        if(!t_windowEvent.isHandled() && nextDispatcher())
        {
            nextDispatcher()(std::move(t_windowEvent));
        }

        if(!t_windowEvent.isHandled() && t_windowEvent.isDispatched())
        {
            Helpers::Logger::log<EventSystem::Event<WindowEvent>>() -> warn(
                "[Unhandled]"); 
        }
    }

    void WindowEventListener::registerResizeCallback(std::function<void(WindowEvent&)>&& t_callback)
    {
        registerCallback(WindowEvent::WindowEventType::RESIZE, std::move(t_callback));
    }
}