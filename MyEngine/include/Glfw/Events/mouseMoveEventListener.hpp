#pragma once

#include "EventSystem/eventListener.hpp"
#include "Glfw/Events/mouseMoveEvent.hpp"

#include <functional>

namespace MyEngine::Glfw::Events
{
    class MouseMoveEventListener: public EventSystem::EventListener<MouseMoveEvent>
    {
    public:
        unsigned int registerMoveCallback(std::function<void(MouseMoveEvent&)>&& t_func);
    private:
        unsigned int m_lastId = 0;
    };
}