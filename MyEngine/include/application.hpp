#pragma once

#include <iostream>
#include <GLFW/glfw3.h>
#include <memory>

namespace MyEngine
{
    //Represents whole application.
    class Application
    {
    public:
        Application(std::string& t_title, int t_w, int t_h) 
            : m_title(t_title), m_screenWidth(t_w), m_screenHeight(t_h) { };
        virtual ~Application();

        // Set up window.
        int initialize();
        // Start the main loop.
        void startLoop();

        // Functions for overriding:
        // Called after window was created.
        virtual bool onWindowCreate() { return true; };
        // Called before the main loop starts.
        virtual bool onLoopStart() { return true; };
        // Called inside the main loop.
        virtual bool onLoop() = 0;
        // Called after main loop ends.
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
