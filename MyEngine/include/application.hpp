#pragma once

#include "window.hpp"
#include "event.hpp"
#include "keyEventListener.hpp"

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

        void setKeyCallback(std::function<void(KeyEvent&)>&& t_callback, KeyEvent::Key t_key, 
            KeyEvent::KeyEventType t_keyEventType = KeyEvent::KeyEventType::keyPressedEvent, 
            KeyEvent::KeyMods t_mods = KeyEvent::KeyMods::none);

        std::string title() const { return m_window.title(); }
        int screenWidth() const { return m_window.screenWidth(); }
        int screenHeight() const { return m_window.screenHeight(); }
    private:
        void onEvent(Event&& event);
        Window m_window;
        KeyEventListener m_keyEventListener;
    };

    std::unique_ptr<Application> CreateApplication();
} 
