#pragma once

#include "event.hpp"
#include "keyEvent.hpp"
#include "mouseKeyEvent.hpp"
#include "mouseMoveEvent.hpp"

#include <GLFW/glfw3.h>
#include <string>
#include <functional>

namespace MyEngine::Glfw
{
    struct WindowParams
    {
        std::string m_title = "";
        int m_screenWidth = 0;
        int m_screenHeight = 0;

        std::function<void(EventSystem::Event&&)> m_eventCallback; 
    };
    

    class Window
    {
    public:
        ~Window();

        void setParams(WindowParams&& t_params);
        bool initializeWindow();
        void pollEvents() const;
        void draw() const;
        bool isActive() const;

        void listenForAllEvents() const;
        void listenForKeyEvents() const;
        void listenForMouseKeyEvents() const;
        void listenForMouseMoveEvents() const;

        std::string title() const { return m_params.m_title; }
        int screenWidth() const { return m_params.m_screenWidth; }
        int screenHeight() const { return m_params.m_screenHeight; }
        bool initialzed() const { return m_window != nullptr; }

    private:
        GLFWwindow *m_window = nullptr;

        WindowParams m_params;
    };
}