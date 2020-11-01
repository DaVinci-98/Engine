#pragma once

#include "EventSystem/event.hpp"

namespace MyEngine::Glfw::Events
{
    class MouseMoveEvent: public EventSystem::Event<MouseMoveEvent>
    {
    public:
        MouseMoveEvent(double t_xPos, double t_yPos, double t_xVec, double t_yVec):
            m_xPos(t_xPos), m_yPos(t_yPos), m_xVec(t_xVec), m_yVec(t_yVec) { }
        inline auto pos() const { return m_xPos, m_yPos; }
        inline auto vec() const { return m_xVec, m_yVec; }

    private:
        double m_xPos;
        double m_yPos;
        double m_xVec;
        double m_yVec;
    };
}