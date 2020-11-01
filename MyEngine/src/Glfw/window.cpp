#include "Glfw/window.hpp"

#include <iostream>

namespace MyEngine::Glfw
{
    Events::KeyEventEmitter& Window::listenForKeyEvents()
    {
        using Events::KeyEvent;
        auto callback = [](GLFWwindow* t_window, int t_key, int t_scancode, int t_action, int t_mods) -> void
        {
            Window* user = (Window*)glfwGetWindowUserPointer(t_window);

            if(t_key < 0 || t_action < 0 || t_mods < 0) return;

            KeyEvent::KeyMods mods = static_cast<KeyEvent::KeyMods>(t_mods);
            KeyEvent::Key key = static_cast<KeyEvent::Key>(t_key);
            KeyEvent::KeyEventType keyEventType = static_cast<KeyEvent::KeyEventType>(t_action);
            
            user -> m_keyEventEmitter.sendEvent(mods, key, keyEventType);
        };

        glfwSetKeyCallback(m_window, callback);
        return m_keyEventEmitter;
    }

    Events::MouseKeyEventEmitter&  Window::listenForMouseKeyEvents()
    {
        using Events::MouseKeyEvent;
        auto callback = [](GLFWwindow* t_window, int t_button, int t_action, int t_mods) -> void
        {
            Window* user = (Window*)glfwGetWindowUserPointer(t_window);

            if(t_button < 0 || t_action < 0 || t_mods < 0) return;

            MouseKeyEvent::KeyMods mods = static_cast<MouseKeyEvent::KeyMods>(t_mods);
            MouseKeyEvent::Key key = static_cast<MouseKeyEvent::Key>(t_button);
            MouseKeyEvent::KeyEventType keyEventType = static_cast<MouseKeyEvent::KeyEventType>(t_action);

            user->m_mouseKeyEventEmitter.sendEvent(mods, key, keyEventType);
        };
        glfwSetMouseButtonCallback(m_window, callback);
        return m_mouseKeyEventEmitter;
    }

    Events::MouseMoveEventEmitter&  Window::listenForMouseMoveEvents()
    {
        auto callback = [](GLFWwindow* t_window, double t_xPos, double t_yPos) -> void
        {
            Window* user = (Window*)glfwGetWindowUserPointer(t_window);
            user->m_mouseMoveEventEmitter.sendEvent(t_xPos, t_yPos);
        };
        glfwSetCursorPosCallback(m_window, callback);
        return m_mouseMoveEventEmitter;
    }

    void Window::pollEvents() const
    {
        glfwPollEvents();
    }

    void Window::draw() const
    {
        glfwSwapBuffers(m_window);
    }

    void Window::setParams(std::string& t_title, unsigned int t_height, unsigned int t_width)
    {
        m_title = t_title;
        m_screenHeight = t_height;
        m_screenWidth = t_width;
    }

    bool Window::isActive() const
    {
        bool active = true;
        active &= !glfwWindowShouldClose(m_window);
        return active;
    }

    bool Window::initializeWindow()
    {
        if (!glfwInit()) return false;

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        m_window = glfwCreateWindow(m_screenWidth, m_screenHeight, m_title.c_str(), NULL, NULL);
        if (!m_window)
        {
            glfwTerminate();
            return false;
        }

        glfwMakeContextCurrent(m_window);

        glfwSwapInterval(1);

        glfwSetWindowUserPointer(m_window, this);

        glfwSetInputMode(m_window, GLFW_LOCK_KEY_MODS, GLFW_TRUE);
        
        return true;
    }

    Window::~Window()
    {
        if(initialzed())
        {
            glfwDestroyWindow(m_window);
            glfwTerminate();
        }
    }

}