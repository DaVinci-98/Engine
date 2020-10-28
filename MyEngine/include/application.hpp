#pragma once

#include "window.hpp"
#include "event.hpp"
#include "keyEventListener.hpp"
#include "eventManager.hpp"

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

        template<typename EventType>
        void setListener(EventSystem::EventListener<EventType>&& t_listener);
        
        std::string title() const { return m_window.title(); }
        int screenWidth() const { return m_window.screenWidth(); }
        int screenHeight() const { return m_window.screenHeight(); }
    private:
        Glfw::Window m_window;
        EventSystem::EventManager<Glfw::KeyEvent> m_keyEventManager;
    };

    std::unique_ptr<Application> CreateApplication();
} 
