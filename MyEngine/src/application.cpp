#include "glad/glad.h"

#include "application.hpp"
#include "OpenGL/indexBuffer.hpp"
#include "OpenGL/vertexBuffer.hpp"
#include "OpenGL/vertexArray.hpp"
#include "OpenGL/shader.hpp"
#include "OpenGL/glException.hpp"
#include "Renderer/renderer.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <iostream>
#include <stdexcept>
#include <exception>
#include <string>

namespace MyEngine
{
    Application::Application(std::string& t_title, int t_w, int t_h, bool t_vsync, bool t_allowResize)
    {
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

    int Application::initialize()
    {
        if(!m_window.initializeWindow()) return -1;

        registerGlfwListeners();

        if(m_window.allowResize()) enableResize();

        if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) return -1;

        GL_CALL(glEnable(GL_BLEND));
        GL_CALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        std::cout << "[VERSION] : " <<  glGetString(GL_VERSION) << std::endl;

        return 0;
    }

    void Application::startLoop()
    {
        while (m_window.isActive())
        {
            bool frame = onLoop();
            if(!frame)
            {
                onLoopEnd();
                return;
            }

            m_window.draw();
            m_window.pollEvents();
        }
        bool end = onLoopEnd();
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
            };
        m_resizeRendererListener.registerResizeCallback(resizeCallback);
    }
}
