#include "Glfw/window.hpp"
#include "Glfw/Events/mouseMoveEvent.hpp"
#include "Glfw/Events/windowEvent.hpp"
#include "Helpers/logger.hpp"
#include "Helpers/type.hpp"

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

        Helpers::Logger::log<Window>() -> info("[Start] [Glfw] [Listener]: {}", Helpers::getTypeName<Events::KeyEvent>());

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

            double xpos, ypos;
            glfwGetCursorPos(user -> m_window, &xpos, &ypos);

            user->m_mouseKeyEventEmitter.sendEvent(mods, key, keyEventType, xpos, ypos);
        };
        glfwSetMouseButtonCallback(m_window, callback);

        Helpers::Logger::log<Window>() -> info("[Start] [Glfw] [Listener]: {}", Helpers::getTypeName<Events::MouseKeyEvent>());

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

        Helpers::Logger::log<Window>() -> info("[Start] [Glfw] [Listener]: {}", Helpers::getTypeName<Events::MouseMoveEvent>());

        return m_mouseMoveEventEmitter;
    }

    Events::WindowEventEmitter&  Window::listenForWindowResizeEvents()
    {
        auto callback = [](GLFWwindow* t_window, int t_width, int t_height) -> void
        {
            Window* user = (Window*)glfwGetWindowUserPointer(t_window);
            user->m_windowEventEmitter.sendEvent(Events::WindowEvent::WindowEventType::RESIZE, 
                user->m_params.m_width, user->m_params.m_height, t_width, t_height);
            user->m_params.m_width = t_width;
            user->m_params.m_height = t_height;
        };
        glfwSetFramebufferSizeCallback(m_window, callback);

        Helpers::Logger::log<Window>() -> info("[Start] [Glfw] [Listener]: {}", Helpers::getTypeName<Events::WindowEvent>());

        return m_windowEventEmitter;
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
        m_params = t_params;
        Helpers::Logger::log<Window>() -> info(
            "[Set] [Window] [Params]:\n"
            "\t[Title]:   {0}\n"
            "\t[Width]:   {1}\n"
            "\t[Height]:  {2}\n"
            "\t[V-sync]:  {3}\n"
            "\t[Rescale]: {4}",  
            t_params.m_title, t_params.m_width, t_params.m_height, t_params.m_vsync, t_params.m_allowResize);
    }

    bool Window::initializeWindow()
    {
        if (!glfwInit()) return false;

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        Helpers::Logger::log<Window>() -> info(
            "[Set] [Glfw] [Params]:\n" 
            "\t[Version]: 4.6\n" 
            "\t[Profile]: core");

        if(m_params.m_allowResize) glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
        else glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

        m_window = glfwCreateWindow(m_params.m_width, m_params.m_height, m_params.m_title.c_str(), NULL, NULL);
        if (!m_window)
        {
            glfwTerminate();
            return false;
        }

        glfwMakeContextCurrent(m_window);

        if(m_params.m_vsync) glfwSwapInterval(1);
        else glfwSwapInterval(0);

        glfwSetWindowUserPointer(m_window, this);

        glfwSetInputMode(m_window, GLFW_LOCK_KEY_MODS, GLFW_TRUE);

        Helpers::Logger::log<Window>() -> info("[Init]: Done");
        
        return true;
    }

    Window::~Window()
    {
        if(initialzed())
        {
            glfwDestroyWindow(m_window);
            glfwTerminate();
        }

        Helpers::Logger::log<Window>() -> info("[Destroy]: Done");
    }
}