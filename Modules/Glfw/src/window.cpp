#include "glad/gl.h"

#include "Glfw/window.hpp"
#include "Logger/logger.hpp"

namespace MyEngine::Glfw
{
    Events::KeyEventEmitter& Window::listenForKeyEvents()
    {
        if(!isActive())
        {
            Logger::Logger::log<Window>() -> error(
                "[Start] [Glfw] [Listener]: Window has to be created before it can start to listen for {}.", 
                typeid(Events::KeyEvent).name());
            return m_keyEventEmitter;
        }
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

        Logger::Logger::log<Window>() -> info(
            "[Start] [Glfw] [Listener]: {}", typeid(Events::KeyEvent).name());

        return m_keyEventEmitter;
    }

    Events::MouseKeyEventEmitter&  Window::listenForMouseKeyEvents()
    {
        if(!isActive())
        {
            Logger::Logger::log<Window>() -> error(
                "[Start] [Glfw] [Listener]: Window has to be created before it can start to listen for {}.", 
                typeid(Events::MouseKeyEvent).name());
            return m_mouseKeyEventEmitter;
        }
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

        Logger::Logger::log<Window>() -> info(
            "[Start] [Glfw] [Listener]: {}", typeid(Events::MouseKeyEvent).name());

        return m_mouseKeyEventEmitter;
    }

    Events::MouseMoveEventEmitter&  Window::listenForMouseMoveEvents()
    {
        if(!isActive())
        {
            Logger::Logger::log<Window>() -> error(
                "[Start] [Glfw] [Listener]: Window has to be created before it can start to listen for {}.", 
                typeid(Events::MouseMoveEvent).name());
            return m_mouseMoveEventEmitter;
        }
        auto callback = [](GLFWwindow* t_window, double t_xPos, double t_yPos) -> void
        {
            Window* user = (Window*)glfwGetWindowUserPointer(t_window);
            user->m_mouseMoveEventEmitter.sendEvent(t_xPos, t_yPos);
        };
        glfwSetCursorPosCallback(m_window, callback);

        Logger::Logger::log<Window>() -> info(
            "[Start] [Glfw] [Listener]: {}", typeid(Events::MouseMoveEvent).name());

        return m_mouseMoveEventEmitter;
    }

    Events::WindowEventEmitter&  Window::listenForWindowResizeEvents()
    {
        if(!isActive())
        {
            Logger::Logger::log<Window>() -> error(
                "[Start] [Glfw] [Listener]: Window has to be created before it can start to listen for {}.", 
                typeid(Events::WindowEvent).name());
            return m_windowEventEmitter;
        }
        auto callback = [](GLFWwindow* t_window, int t_width, int t_height) -> void
        {
            Window* user = (Window*)glfwGetWindowUserPointer(t_window);
            user->m_windowEventEmitter.sendEvent(user->m_params.m_width, user->m_params.m_height, t_width, t_height);
            user->m_params.m_width = t_width;
            user->m_params.m_height = t_height;
        };
        glfwSetFramebufferSizeCallback(m_window, callback);

        Logger::Logger::log<Window>() -> info(
            "[Start] [Glfw] [Listener]: {}", typeid(Events::WindowEvent).name());

        return m_windowEventEmitter;
    }

    void Window::pollEvents() const
    {
        if(!isActive())
            Logger::Logger::log<Window>() -> error(
                "[pollEvents()]: Window's params have to be set before calling this function.");
        glfwPollEvents();
    }

    void Window::draw() const
    {
        if(!isActive())
            Logger::Logger::log<Window>() -> error(
                "[draw()]: Window's params have to be set before calling this function.");
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
        m_params = std::move(t_params);
        m_paramsSet = true;
        Logger::Logger::log<Window>() -> info(
            "[Set] [Window] [Params]:\n"
            "\t[Title]:   {0}\n"
            "\t[Width]:   {1}\n"
            "\t[Height]:  {2}\n"
            "\t[V-sync]:  {3}\n"
            "\t[Rescale]: {4}",  
            m_params.m_title, m_params.m_width, m_params.m_height, m_params.m_vsync, m_params.m_allowResize);
    }

    bool Window::initializeWindow()
    {
        if(!m_paramsSet)
        {
            Logger::Logger::log<Window>() -> error(
                "[Init]: Window's params have to be set before init.");
            return false;
        }

        if (!glfwInit())
        {
            int error = glfwGetError(nullptr);
            Logger::Logger::log<Window>() -> error(
                "[Init] [{0}]: Couldn't initialize Glfw.",
                error);
            return false;
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        if(m_params.m_allowResize) glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
        else glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

        m_window = glfwCreateWindow(m_params.m_width, m_params.m_height, m_params.m_title.c_str(), NULL, NULL);
        if (!m_window)
        {
            int error = glfwGetError(nullptr);
            glfwTerminate();
            Logger::Logger::log<Window>() -> error(
                "[Init] [{0}]: Couldn't create Glfw window.",
                error);
            return false;
        }

        glfwMakeContextCurrent(m_window);
        
        int version = gladLoadGL(glfwGetProcAddress);
        if (!version)
        {
            Logger::Logger::log<Window>() -> error(
                "[Init]: GL loader couldn't be loaded."); 
            return false;
        }
        else
        {
            Logger::Logger::log<Window>() -> info(
                "[Init] [glad]: Done\n" 
                "\t[Version]: {0}.{1}\n"
                "\t[Vendor]: {2}",
                GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version), 
                (const char*)glGetString(GL_VENDOR)); 
        }

        if(m_params.m_vsync) glfwSwapInterval(1);
        else glfwSwapInterval(0);

        glfwSetWindowUserPointer(m_window, this);

        glfwSetInputMode(m_window, GLFW_LOCK_KEY_MODS, GLFW_TRUE);

        Logger::Logger::log<Window>() -> info(
            "[Init]: Done");
        
        return true;
    }

    Window::~Window()
    {
        if(initialzed())
        {
            glfwDestroyWindow(m_window);
            glfwTerminate();
        }

        Logger::Logger::log<Window>() -> info(
            "[Destroy]: Done");
    }
}