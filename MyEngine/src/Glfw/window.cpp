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

    // void Window::listenForMouseKeyEvents()
    // {
    //     TODO
    //     auto callback = [](GLFWwindow* t_window, int t_key, int t_scancode, int t_action, int t_mods) -> void
    //     {
    //         WindowParams* user = (WindowParams*)glfwGetWindowUserPointer(t_window);
    //         MouseKeyEvent event;
    //         user->m_eventCallback(std::move(event));
    //     };
    //     glfwSetKeyCallback(m_window, callback);
    // }

    // void Window::listenForMouseMoveEvents()
    // {
    //     TODO
    //     auto callback = [](GLFWwindow* t_window, int t_key, int t_scancode, int t_action, int t_mods) -> void
    //     {
    //         WindowParams* user = (WindowParams*)glfwGetWindowUserPointer(t_window);
    //         MouseMoveEvent event;
    //         user->m_eventCallback(std::move(event));
    //     };
    //     glfwSetKeyCallback(m_window, callback);
    // }

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