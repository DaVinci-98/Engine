#pragma once

#include "EventSystem/eventEmitter.hpp"
#include "Glfw/Events/mouseMoveEvent.hpp"

namespace MyEngine::Glfw::Events
{
    class MouseMoveEventEmitter: public EventSystem::EventEmitter<MouseMoveEvent>
    {
    public:
        void sendEvent(double t_posX, double t_posY);
    private:
        double m_lastX = 0;
        double m_lastY = 0;
    };
}