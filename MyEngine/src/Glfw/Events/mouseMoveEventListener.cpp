#include "Glfw/Events/mouseMoveEventListener.hpp"

namespace MyEngine::Glfw::Events
{
    unsigned int MouseMoveEventListener::registerMoveCallback(std::function<void(MouseMoveEvent&)>&& t_func)
    {
        registerCallback(m_lastId, std::move(t_func));
        return m_lastId++;
    }
}