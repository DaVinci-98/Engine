#pragma once

#include "EventSystem/event.hpp"
#include "Glfw/Events/keyEvent.hpp"
#include "Glfw/Events/keyEventEmitter.hpp"
#include "Glfw/Events/mouseKeyEvent.hpp"
#include "Glfw/Events/mouseKeyEventEmitter.hpp"
#include "Glfw/Events/mouseMoveEvent.hpp"
#include "Glfw/Events/mouseMoveEventEmitter.hpp"
#include "Glfw/Events/windowEvent.hpp"
#include "Glfw/Events/windowEventEmitter.hpp"

#include <GLFW/glfw3.h>
#include <string>
#include <functional>

namespace MyEngine::Glfw
{
    class Window
    {
    public:
        struct WindowParams
        {
            std::string m_title;
            unsigned int m_width;
            unsigned int m_height;
            bool m_vsync;
            bool m_allowResize;
        };

        ~Window();

        void setParams(WindowParams&& t_params);
        bool initializeWindow();
        void pollEvents() const;
        void draw() const;
        bool isActive() const;

        Events::KeyEventEmitter& listenForKeyEvents();
        Events::MouseKeyEventEmitter& listenForMouseKeyEvents();
        Events::MouseMoveEventEmitter& listenForMouseMoveEvents();
        Events::WindowEventEmitter& listenForWindowResizeEvents();

        inline std::string title() const { return m_params.m_title; }
        inline int screenWidth() const { return m_params.m_width; }
        inline int screenHeight() const { return m_params.m_height; }
        inline bool allowResize() const { return m_params.m_allowResize; }
        inline bool initialzed() const { return m_window != nullptr; }

    private:
        GLFWwindow *m_window = nullptr;

        WindowParams m_params;
        
        Events::KeyEventEmitter m_keyEventEmitter;
        Events::MouseKeyEventEmitter m_mouseKeyEventEmitter;
        Events::MouseMoveEventEmitter m_mouseMoveEventEmitter;
        Events::WindowEventEmitter m_windowEventEmitter;
    };
}