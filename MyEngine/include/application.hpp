#pragma once

#include "Glfw/window.hpp"
#include "Glfw/Events/keyEventListener.hpp"
#include "Glfw/Events/mouseKeyEventListener.hpp"
#include "EventSystem/event.hpp"

#include <iostream>
#include <memory>
#include <unordered_map>

namespace MyEngine
{
    //Represents whole application.
    class Application
    {
    public:
        Application(std::string& t_title, int t_w, int t_h);

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
        
        inline std::string title() const { return m_window.title(); }
        inline int screenWidth() const { return m_window.screenWidth(); }
        inline int screenHeight() const { return m_window.screenHeight(); }

        inline Glfw::Events::KeyEventListener& keyEventListener() { return m_keyEventListener; }
    private:
        Glfw::Window m_window;
        Glfw::Events::KeyEventListener m_keyEventListener;
        Glfw::Events::MouseKeyEventListener m_mouseKeyEventListener;
    };

    std::unique_ptr<Application> CreateApplication();
} 
