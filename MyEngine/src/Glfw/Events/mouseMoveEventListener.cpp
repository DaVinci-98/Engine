#include "Glfw/Events/mouseMoveEventListener.hpp"
#include "Helpers/logger.hpp"
#include "EventSystem/event.hpp"

namespace MyEngine::Glfw::Events
{
    void MouseMoveEventListener::dispatch(MouseMoveEvent&& t_event)
    {
        for (auto& [_, t_callback] : m_callbackMap)
        {
            t_event.dispatched();
            t_callback(t_event);
            if(t_event.isHandled()) return;
        }

        if(!t_event.isHandled() && t_event.isDispatched())
        {
            Helpers::Logger::log<EventSystem::Event<MouseMoveEvent>>(Helpers::Logger::LogType::WARN,
                "[Unhandled]"); 
        }
    }

    unsigned int MouseMoveEventListener::registerMoveCallback(std::function<void(MouseMoveEvent&)>&& t_func)
    {
        registerCallback(m_lastId, std::move(t_func));
        return m_lastId++;
    }
}