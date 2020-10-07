#pragma once

#include <GLFW/glfw3.h>
#include <string>

namespace MyEngine
{
    struct WindowParams
    {
        std::string m_title = "";
        int m_screenWidth = 0;
        int m_screenHeight = 0;
    };
    

    class Window
    {
    public:
        void setParams(WindowParams&& t_params);
        bool initializeWindow();
        void pollEvents() const;
        void draw() const;
        bool isActive() const;

        std::string title() const { return m_params.m_title; }
        int screenWidth() const { return m_params.m_screenWidth; }
        int screenHeight() const { return m_params.m_screenHeight; }
        bool initialzed() const { return m_window != nullptr; }

    private:
        GLFWwindow *m_window = nullptr;

        WindowParams m_params;
    }
}