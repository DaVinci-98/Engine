#pragma once

#include "Glfw/window.hpp"
#include "Glfw/Events/keyEventListener.hpp"
#include "Glfw/Events/mouseKeyEventListener.hpp"
#include "Glfw/Events/mouseMoveEventListener.hpp"
#include "Glfw/Events/windowEventListener.hpp"
#include "EventSystem/event.hpp"
#include "Renderer/renderer.hpp"
#include "Physics/physicsManager.hpp"

#include <iostream>
#include <memory>
#include <unordered_map>

namespace MyEngine
{
    //Represents whole application.
    class Application
    {
    public:
        Application(std::string& t_title, int t_w, int t_h, bool t_vsync, bool t_allowResize);
        ~Application();

        // Set up window.
        int initialize();
        // Start the main loop.
        void startLoop();

        // Functions for overriding:
        // Called after window was created.
        virtual bool onWindowCreate() 
            { return true; };
        // Called inside the main loop.
        virtual bool onLoop() = 0;
        // Called after main loop ends.
        virtual bool onLoopEnd() 
            { return true; };
        
        inline std::string title() const 
            { return m_window.title(); }
        inline int screenWidth() const 
            { return m_window.screenWidth(); }
        inline int screenHeight() const 
            { return m_window.screenHeight(); }
        inline Renderer::Renderer& renderer() 
            { return m_renderer; }

        inline Glfw::Events::KeyEventListener& keyEventListener() 
            { return m_keyEventListener; }
        inline Glfw::Events::MouseKeyEventListener& mouseKeyEventListener() 
            { return m_mouseKeyEventListener; }
        inline Glfw::Events::MouseMoveEventListener& mouseMoveEventListener() 
            { return m_mouseMoveEventListener; }
        inline Glfw::Events::WindowEventListener& windowEventListener() 
            { return m_windowEventListener; }

        inline Physics::PhysicsManager& physicsManager()
            {return m_physicsManager; }
                
    private:
        void registerGlfwListeners();
        void enableResize();

        Physics::PhysicsManager m_physicsManager;
        Renderer::Renderer m_renderer;
        Glfw::Window m_window;
        
        Glfw::Events::KeyEventListener m_keyEventListener;
        Glfw::Events::MouseKeyEventListener m_mouseKeyEventListener;
        Glfw::Events::MouseMoveEventListener m_mouseMoveEventListener;
        Glfw::Events::WindowEventListener m_windowEventListener;
        Glfw::Events::WindowEventListener m_resizeRendererListener;
    };

    std::unique_ptr<Application> CreateApplication();
} 
