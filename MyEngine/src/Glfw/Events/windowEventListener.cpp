#include "Glfw/Events/windowEventListener.hpp"

namespace MyEngine::Glfw::Events
{
    void WindowEventListener::dispatch(WindowEvent&& t_event)
    {
        WindowEvent::WindowEventType type = t_event.evntType();
        if(callback(type))
        {
            t_event.setDispatched();
            callback(type)(t_event);
        }

        if(!t_event.isHandled() && nextDispatcher())
        {
            nextDispatcher()(std::move(t_event));
        }
    }

    void WindowEventListener::registerResizeCallback(std::function<void(WindowEvent&)>&& t_callback)
    {
        registerCallback(WindowEvent::WindowEventType::RESIZE, std::move(t_callback));
    }
}