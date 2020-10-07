#include "window.hpp"
#include "glException.hpp"

namespace MyEngine
{
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
        
        return true;
    }

    Window::~Window()
    {
        try
        {   
            if(initialzed())
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