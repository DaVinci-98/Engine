#pragma once

#include "EventSystem/event.hpp"
#include "Glfw/keyEvent.hpp"
#include "Glfw/mouseKeyEvent.hpp"
#include "Glfw/mouseMoveEvent.hpp"
#include "Glfw/keyEventEmitter.hpp"

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

        KeyEventEmitter m_keyEventEmitter;
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