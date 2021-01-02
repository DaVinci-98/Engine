#pragma once

#include "EventSystem/event.hpp"

#include <tuple>

namespace MyEngine::Glfw::Events
{
    /**
     * @brief Event for sending informations related to window.
     * 
     */
    class WindowEvent: public EventSystem::Event<WindowEvent>
    {
    public:
        /**
         * @brief Type of the WindowEvent (currently only resize).
         * 
         */
        enum WindowEventType
        {
            RESIZE
        };

        /**
         * @brief Construct a new WindowEvent object of type Resize.
         * 
         * @param t_oldWidth window width before change
         * @param t_oldHeight window height before change 
         * @param t_newWidth window width after change
         * @param t_newHeight window height after change
         */
        WindowEvent(int t_oldWidth, int t_oldHeight, int t_newWidth, int t_newHeight):
            m_type(WindowEventType::RESIZE), m_oldWidth(t_oldWidth), m_oldHeight(t_oldHeight), 
            m_newWidth(t_newWidth), m_newHeight(t_newHeight) { }
        
        /**
         * @brief Type of the WindowEvent.
         * 
         */
        inline WindowEventType evntType() const 
            { return m_type; }
        /**
         * @brief New size of the window.
         * 
         * @return std::tuple of int, int - (width, height)
         */
        inline std::tuple<int, int> newWindowSize() const 
            { return std::make_tuple(m_newWidth, m_newHeight); }
        /**
         * @brief Old size of the window.
         * 
         * @return std::tuple of int, int - (width, height)
         */
        inline std::tuple<int, int> oldWindowSize() const 
            { return std::make_tuple(m_oldWidth, m_oldHeight); }
            
    private:
        WindowEventType m_type;
        int m_newWidth;
        int m_newHeight;
        int m_oldWidth;
        int m_oldHeight;
    };
}