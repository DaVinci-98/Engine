#include "Application/application.hpp"
#include "Logger/logger.hpp"

#include <stdexcept>
#include <exception>

namespace MyEngine
{

    Application::~Application()
    {
        Logger::Logger::log<Application>() -> info( 
            "[Destroy]: Done");
    }

    Application::Application(std::string& t_title, int t_w, int t_h, bool t_vsync, bool t_allowResize, float t_updateRate)
    {
        m_updateRate = t_updateRate;
        Glfw::Window::WindowParams params 
        { 
            .m_title = t_title, 
            .m_width = static_cast<unsigned int>(t_w), 
            .m_height = static_cast<unsigned int>(t_h), 
            .m_vsync = t_vsync, 
            .m_allowResize = t_allowResize 
        };
        m_window.setParams(std::move(params));
    }

    bool Application::initialize()
    {
        if(!m_window.initializeWindow())
        {
            Logger::Logger::log<Application>() -> error(
                "[Init]: Couldn't initialize Glfw window.");
            return false;
        }
        if(m_window.allowResize()) 
            enableResize();
        registerGlfwListeners();

        if(!m_renderer.initialize())
        {
            Logger::Logger::log<Application>() -> error(
                "[Init]: Couldn't initialize renderer.");
            return false;
        }
        renderer().registerDrawableAddEventEmitter(m_drawableAddEventEmitter);
        renderer().setOrtho2D(screenWidth(), screenHeight());

        Logger::Logger::log<Application>() -> info(
            "[Version]: {}", glGetString(GL_VERSION));
        Logger::Logger::log<Application>() -> info(
            "[Init]: Done");
        
        return true;
    }

    void Application::startLoop()
    {
        Logger::Logger::log<Application>() -> info(
            "[Start] [Game loop]");
        auto currentTime = std::chrono::steady_clock::now();
        float accumulator = 0.0f;

        while (m_window.isActive())
        {
            auto newTime = std::chrono::steady_clock::now();
            float frameTime = std::chrono::duration_cast<std::chrono::duration<float>>(newTime - currentTime).count();
            bool frame = true;
            currentTime = newTime;

            accumulator += frameTime;
            while(accumulator > m_updateRate)
            {
                physicsManager().update(m_updateRate);
                frame = onUpdate(m_updateRate);
                accumulator -= m_updateRate;
            }

            if(frame)
            {
                m_renderer.clear();
                frame = onRender();
                if(frame) 
                    frame = m_renderer.drawFromQueue();
            }
            if(!frame)
            {
                onLoopEnd();
                Logger::Logger::log<Application>() -> info(
                    "[End] [Game loop]");
                return;
            }

            m_window.draw();
            m_window.pollEvents();
        }
        bool end = onLoopEnd();
        Logger::Logger::log<Application>() -> info(
            "[End] [Game loop]");
        return;
    }

    void Application::registerGlfwListeners()
    {
        m_keyEventListener.registerEmitter(m_window.listenForKeyEvents());
        m_mouseKeyEventListener.registerEmitter(m_window.listenForMouseKeyEvents());
        m_mouseMoveEventListener.registerEmitter(m_window.listenForMouseMoveEvents());
    }

    void Application::enableResize()
    {
        m_resizeRendererListener.registerEmitter(m_window.listenForWindowResizeEvents());
        m_resizeRendererListener.registerNextListener(m_windowEventListener);
        
        auto resizeCallback = [this](Glfw::Events::WindowEvent& t_event) -> void 
        {
            auto&& [width, height] = t_event.newWindowSize();
            this->m_renderer.resizeWindow(width, height); 
            t_event.handle();
        };
        m_resizeRendererListener.registerResizeCallback(resizeCallback);
    }
}
