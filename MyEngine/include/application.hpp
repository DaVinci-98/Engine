#pragma once

#include "Glfw/window.hpp"
#include "Glfw/Events/keyEventListener.hpp"
#include "Glfw/Events/mouseKeyEventListener.hpp"
#include "Glfw/Events/mouseMoveEventListener.hpp"
#include "Glfw/Events/windowEventListener.hpp"
#include "EventSystem/event.hpp"
#include "Renderer/renderer.hpp"
#include "Renderer/drawable2D.hpp"
#include "Renderer/Events/drawableAddEventEmitter.hpp"
#include "Physics/physicsManager.hpp"

#include <iostream>
#include <memory>
#include <unordered_map>
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

        /**
         * @brief Add Drawable to render queue with callback function which will be called before render.
         * 
         * @param t_drawable Object which will be drawn.
         * @param t_callback Function to call before drawing the object.
         */
        inline void addToRenderQueue(std::shared_ptr<Renderer::Drawable2D> t_drawable, std::function<void(void)>&& t_callback)
            { m_drawableAddEventEmitter.sendEvent(t_drawable, std::move(t_callback)); }

        /**
         * @brief Get a reference to underlying KeyEventListener.
         * 
         */
        inline Glfw::Events::KeyEventListener& keyEventListener() 
            { return m_keyEventListener; }
        /**
         * @brief Get a reference to underlying MouseKeyEventListener.
         * 
         */
        inline Glfw::Events::MouseKeyEventListener& mouseKeyEventListener() 
            { return m_mouseKeyEventListener; }
        /**
         * @brief Get a reference to underlying MouseMoveEventListener.
         * 
         */
        inline Glfw::Events::MouseMoveEventListener& mouseMoveEventListener() 
            { return m_mouseMoveEventListener; }
        /**
         * @brief Get a reference to underlying WindowEventListener.
         * 
         */
        inline Glfw::Events::WindowEventListener& windowEventListener() 
            { return m_windowEventListener; }

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
        
        Renderer::Events::DrawableAddEventEmitter m_drawableAddEventEmitter;
        Glfw::Events::KeyEventListener m_keyEventListener;
        Glfw::Events::MouseKeyEventListener m_mouseKeyEventListener;
        Glfw::Events::MouseMoveEventListener m_mouseMoveEventListener;
        Glfw::Events::WindowEventListener m_windowEventListener;
        Glfw::Events::WindowEventListener m_resizeRendererListener;
    };

    std::unique_ptr<Application> CreateApplication();
} 
