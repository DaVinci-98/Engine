#pragma once

#include "Glfw/window.hpp"
#include "Renderer/renderer.hpp"
#include "Renderer/drawable2D.hpp"
#include "Physics/physicsManager.hpp"

#include <memory>
#include <chrono>

namespace MyEngine
{
    /**
     * @brief Represents whole application.
     * 
     */
    class Application
    {
    public:
        /**
         * @brief Construct a new Application object.
         * 
         * @param t_title title for the window
         * @param t_w window's width
         * @param t_h window's height
         * @param t_vsync use vsync
         * @param t_allowResize allow resize of the window
         * @param t_updateRate rate at which physics is updated and onUpdate() function is called.
         */
        Application(std::string& t_title, int t_w, int t_h, bool t_vsync, bool t_allowResize, float t_updateRate = 1.0f/60.0f);

        /**
         * @brief Destroy the Application object.
         * 
         */
        virtual ~Application();

        /**
         * @brief Set up Glfw and Renderer. 
         * 
         * @return true is setup was successful.
         */
        bool initialize();
        /**
         * @brief Start the game loop.
         * 
         */
        void startLoop();

        /**
         * @brief Function after window was created.
         * (overrite for game setup here)
         * 
         * @return true if function was successful
         * 
         */
        virtual bool onWindowCreate() 
            { return true; };
        /**
         * @brief Function which moves logic and physics forward in time.
         * (overrite for game logic here)
         * 
         * @param t_deltaTime time in seconds by which logic and physics will be advanced
         * 
         * @return true if function was successful
         * 
         */
        virtual bool onUpdate(float t_deltaTime)
            { return true; }
        /**
         * @brief Function fro rendering stuff to window.
         * (overrite for rendering game objects here)
         * 
         * @return true if function was successful
         * 
         */
        virtual bool onRender()
            { return true; }
        /**
         * @brief Called after game loop ends.
         * (overrite for cleaning up game objects here)
         * 
         * @return true if function was successful
         * 
         */
        virtual bool onLoopEnd() 
            { return true; };
        
        /**
         * @brief Get window's title.
         * 
         */
        inline std::string title() const 
            { return m_window.title(); }
        /**
         * @brief Get window's width.
         * 
         */
        inline int screenWidth() const 
            { return m_window.screenWidth(); }
        /**
         * @brief Get window's height.
         * 
         */
        inline int screenHeight() const 
            { return m_window.screenHeight(); }
        /**
         * @brief Get a reference to underlying renderer.
         * 
         */
        inline Renderer::Renderer& renderer() 
            { return m_renderer; }

       void registerKeyCallback(std::function<void(Glfw::Events::KeyEvent&&)>&& t_callback, 
            std::tuple<Glfw::Events::KeyEvent::KeyMods, Glfw::Events::KeyEvent::Key, Glfw::Events::KeyEvent::KeyEventType>&& t_key)
            { m_window.registerKeyCallback(std::move(t_callback), std::move(t_key)); }
        void registerMouseKeyCallback(std::function<void(Glfw::Events::MouseKeyEvent&&)>&& t_callback, 
            std::tuple<Glfw::Events::MouseKeyEvent::KeyMods, Glfw::Events::MouseKeyEvent::Key, Glfw::Events::MouseKeyEvent::KeyEventType>&& t_key)
            { m_window.registerMouseKeyCallback(std::move(t_callback), std::move(t_key)); }
        void registerMouseMoveCallback(std::function<void(Glfw::Events::MouseMoveEvent&&)>&& t_callback)
            { m_window.registerMouseMoveCallback(std::move(t_callback)); }
        void registerWindowCallback(std::function<void(Glfw::Events::WindowEvent&&)>&& t_callback)
            { m_windowEventCallback = std::move(t_callback); }

        /**
         * @brief Get a reference to underlying PhysicsManager.
         * 
         */
        inline Physics::PhysicsManager& physicsManager()
            {return m_physicsManager; }
                
    private:
        void registerGlfwListeners();
        void enableResize();

        float m_updateRate = 1.0f / 60.0f;

        Physics::PhysicsManager m_physicsManager;
        Renderer::Renderer m_renderer;
        Glfw::Window m_window;
        std::function<void(Glfw::Events::WindowEvent&&)> m_windowEventCallback;
    };

    std::unique_ptr<Application> CreateApplication();
} 
