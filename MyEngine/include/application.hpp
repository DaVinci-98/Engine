#pragma once

#include "indexBuffer.hpp"
#include "vertexBuffer.hpp"
#include "vertexArray.hpp"
#include "shader.hpp"
#include "texture.hpp"

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>

namespace MyEngine
{
    class Application
    {
    public:
        Application(std::string& t_title, int t_w, int t_h) 
            : m_title(t_title), m_screenWidth(t_w), m_screenHeight(t_h) { };
        virtual ~Application();

        int initialize();
        void startLoop();

        virtual bool onWindowCreate() = 0;
        virtual bool onLoopStart() { return true; };
        virtual bool onLoop() = 0;
        virtual bool onLoopEnd() { return true; };

    private:
        GLFWwindow *m_window = nullptr;
        bool m_glfwInitialized = false;

    protected:

        std::string m_title = "";
        int m_screenWidth = 0;
        int m_screenHeight = 0;
    };

    std::unique_ptr<Application> CreateApplication();
} 
