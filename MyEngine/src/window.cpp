#include "window.hpp"

#include <iostream>

namespace MyEngine
{
    void Window::listenForAllEvents() const
    {
        listenForKeyEvents();
        listenForMouseKeyEvents();
        listenForMouseMoveEvents();
    }

    void Window::listenForKeyEvents() const
    {
        auto callback = [](GLFWwindow* t_window, int t_key, int t_scancode, int t_action, int t_mods) -> void
        {
            WindowParams* user = (WindowParams*)glfwGetWindowUserPointer(t_window);

            if(t_key < 0 || t_action < 0 || t_mods < 0) return;

            KeyEvent::KeyMods mods = static_cast<KeyEvent::KeyMods>(t_mods);
            KeyEvent::Key key = static_cast<KeyEvent::Key>(t_key);
            KeyEvent::KeyEventType keyEventType = static_cast<KeyEvent::KeyEventType>(t_action);
            
            unsigned int keyCode = KeyEvent::getKeyCode(mods, key, keyEventType);

            user->m_eventCallback(KeyEvent(keyCode));
        };

        glfwSetKeyCallback(m_window, callback);
    }

    void Window::listenForMouseKeyEvents() const
    {
        // TODO
        // auto callback = [](GLFWwindow* t_window, int t_key, int t_scancode, int t_action, int t_mods) -> void
        // {
        //     WindowParams* user = (WindowParams*)glfwGetWindowUserPointer(t_window);
        //     MouseKeyEvent event;
        //     user->m_eventCallback(std::move(event));
        // };
        // glfwSetKeyCallback(m_window, callback);
    }

    void Window::listenForMouseMoveEvents() const
    {
        // TODO
        // auto callback = [](GLFWwindow* t_window, int t_key, int t_scancode, int t_action, int t_mods) -> void
        // {
        //     WindowParams* user = (WindowParams*)glfwGetWindowUserPointer(t_window);
        //     MouseMoveEvent event;
        //     user->m_eventCallback(std::move(event));
        // };
        // glfwSetKeyCallback(m_window, callback);
    }

    void Window::pollEvents() const
    {
        glfwPollEvents();
    }

    void Window::draw() const
    {
        glfwSwapBuffers(m_window);
    }

    bool Window::isActive() const
    {
        bool active = true;
        active &= !glfwWindowShouldClose(m_window);
        return active;
    }

    void Window::setParams(WindowParams&& t_params)
    {
        m_params.m_title = t_params.m_title;
        m_params.m_screenWidth = t_params.m_screenWidth;
        m_params.m_screenHeight = t_params.m_screenHeight;
        m_params.m_eventCallback = t_params.m_eventCallback;
    }

    bool Window::initializeWindow()
    {
        if (!glfwInit()) return false;

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        m_window = glfwCreateWindow(m_params.m_screenWidth, m_params.m_screenHeight, m_params.m_title.c_str(), NULL, NULL);
        if (!m_window)
        {
            glfwTerminate();
            return false;
        }

        glfwMakeContextCurrent(m_window);

        glfwSwapInterval(1);

        glfwSetWindowUserPointer(m_window, &m_params);

        listenForAllEvents();

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