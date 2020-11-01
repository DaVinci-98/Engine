#pragma once

#include "EventSystem/event.hpp"
#include "Glfw/Events/keyEvent.hpp"
#include "Glfw/Events/keyEventEmitter.hpp"
#include "Glfw/Events/mouseKeyEvent.hpp"
#include "Glfw/Events/mouseKeyEventEmitter.hpp"
#include "Glfw/Events/mouseMoveEvent.hpp"
#include "Glfw/Events/mouseMoveEventEmitter.hpp"

#include <GLFW/glfw3.h>
#include <string>
#include <functional>

namespace MyEngine::Glfw
{
    class Window
    {
    public:
        ~Window();

        void setParams(std::string& t_title, unsigned int t_height, unsigned int t_width);
        bool initializeWindow();
        void pollEvents() const;
        void draw() const;
        bool isActive() const;

        Events::KeyEventEmitter& listenForKeyEvents();
        Events::MouseKeyEventEmitter& listenForMouseKeyEvents();
        Events::MouseMoveEventEmitter& listenForMouseMoveEvents();

        inline std::string title() const { return m_title; }
        inline int screenWidth() const { return m_screenWidth; }
        inline int screenHeight() const { return m_screenHeight; }
        inline bool initialzed() const { return m_window != nullptr; }

    private:
        GLFWwindow *m_window = nullptr;

        std::string m_title = "";
        int m_screenWidth = 0;
        int m_screenHeight = 0;

        Events::KeyEventEmitter m_keyEventEmitter;
        Events::MouseKeyEventEmitter m_mouseKeyEventEmitter;
        Events::MouseMoveEventEmitter m_mouseMoveEventEmitter;
    };
}