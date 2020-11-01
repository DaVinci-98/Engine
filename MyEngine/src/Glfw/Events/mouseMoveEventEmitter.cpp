#include "Glfw/Events/mouseMoveEventEmitter.hpp"

#include <math.h>

namespace MyEngine::Glfw::Events
{
    void MouseMoveEventEmitter::sendEvent(double t_xPos, double t_yPos)
    {
        double xVec = t_xPos - m_lastX;
        double yVec = t_yPos - m_lastY;

        m_lastX = t_xPos;
        m_lastY = t_yPos;

        EventSystem::EventEmitter<MouseMoveEvent>::sendEvent(MouseMoveEvent(t_xPos, t_yPos, xVec, yVec));
    }
}