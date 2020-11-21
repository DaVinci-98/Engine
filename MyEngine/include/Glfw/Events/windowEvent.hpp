#pragma once

#include "EventSystem/event.hpp"

#include <tuple>

namespace MyEngine::Glfw::Events
{
    class WindowEvent: public EventSystem::Event<WindowEvent>
    {
    public:
        enum WindowEventType
        {
            RESIZE
        };

        WindowEvent(WindowEventType t_type, int t_oldWidth, int t_oldHeight, int t_newWidth, int t_newHeight):
            m_type(t_type), m_oldWidth(t_oldWidth), m_oldHeight(t_oldHeight), 
            m_newWidth(t_newWidth), m_newHeight(t_newHeight) { }
            
        inline WindowEventType evntType() const { return m_type; }
        inline std::tuple<int, int> newWindowSize() const { return std::make_tuple(m_newWidth, m_newHeight); }
        inline std::tuple<int, int> oldWindowSize() const { return std::make_tuple(m_oldWidth, m_oldHeight); }
    private:
        WindowEventType m_type;
        int m_newWidth;
        int m_newHeight;
        int m_oldWidth;
        int m_oldHeight;
    };
}