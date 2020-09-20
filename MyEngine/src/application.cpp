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
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <exception>
#include <string>

namespace MyEngine
{
    int Application::initialize()
    {
        if (!glfwInit()) return -1;
        m_glfwInitialized = true;

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        m_window = glfwCreateWindow(m_screenWidth, m_screenHeight, m_title.c_str(), NULL, NULL);
        if (!m_window)
        {
            glfwTerminate();
            return -1;
        }

        glfwMakeContextCurrent(m_window);

        glfwSwapInterval(1);

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
        while (!glfwWindowShouldClose(m_window))
        {
            glfwPollEvents();

            bool frame = onLoop();
            if(!frame)
            {
                onLoopEnd();
                return;
            }

            glfwSwapBuffers(m_window);
        }
        bool end = onLoopEnd();
        return;
    }

    Application::~Application()
    {
        try
        {   
            if(m_glfwInitialized)
            {
                glfwDestroyWindow(m_window);
                glfwTerminate();
            }
        }
        catch(GlException& e)
        {
            e.printErrors();
        }
    }
}
