#include "glad/glad.h"

#include "application.hpp"
#include "indexBuffer.hpp"
#include "vertexBuffer.hpp"
#include "vertexArray.hpp"
#include "shader.hpp"
#include "glException.hpp"
#include "renderer.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <iostream>
#include <stdexcept>
#include <exception>
#include <string>

namespace MyEngine
{
    Application::Application(std::string& t_title, int t_w, int t_h)
    {
        Glfw::WindowParams params;
        params.m_title = t_title;
        params.m_screenWidth = t_w;
        params.m_screenHeight = t_h;

        m_keyEventManager.registerEmitter(params.m_keyEventEmitter);

        m_window.setParams(std::move(params));
    }

    template<>
    void Application::setListener<Glfw::KeyEvent>(EventSystem::EventListener<Glfw::KeyEvent>&& t_listener)
    {
        m_keyEventManager.registerListener(std::move(t_listener));
    }

    int Application::initialize()
    {
        if(!m_window.initializeWindow())
        {
            return -1;
        }

        if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) 
        {
            return -1;
        }

        GL_CALL(glEnable(GL_BLEND));
        GL_CALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        std::cout << "[VERSION] : " <<  glGetString(GL_VERSION) << std::endl;

        return 0;
    }

    void Application::startLoop()
    {
        bool start = onLoopStart();
        if(!start)
        {
            onLoopEnd();
            return;
        }
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
}
