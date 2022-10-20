#pragma once

#include "Glfw/Events/keyEvent.hpp"
#include "Glfw/Events/mouseKeyEvent.hpp"
#include "Glfw/Events/mouseMoveEvent.hpp"
#include "Glfw/Events/windowEvent.hpp"

#include "GLFW/glfw3.h"
#include <string>
#include <map>
#include <tuple>
#include <functional>

namespace MyEngine::Glfw
{
    /**
     * @brief An abstraction of Glfw window.
     * 
     */
    class Window
    {
    public:
        /**
         * @brief Params used for creating the Window.
         * 
         */
        struct WindowParams
        {
            std::string m_title;
            unsigned int m_width;
            unsigned int m_height;
            // Set false to unlock framerate
            bool m_vsync;
            bool m_allowResize;
        };
        /**
         * @brief Destroy the Window object. Handles destruction of Glfw window.
         * 
         */
        ~Window();

        /**
         * @brief Set Window's params. 
         * Has to be called before initializeWindow().
         * 
         */
        void setParams(WindowParams&& t_params);
        /**
         * @brief Creates a Glfw window, with params provide in setParams() function.
         * @sa glfwInit()
         * @sa glfwCreateWindow()
         * 
         * @return true If Window was initialized.
         */
        bool initializeWindow();
        /**
         * @brief Gather Glfw Events - 
         * necessary if you want to listen for KeyEvent, MouseKeyEvent, MouseMoveEvent, WindowEvent.
         * @sa glfwPollEvents()
         * 
         */
        void pollEvents() const;
        /**
         * @brief Swaps glfw buffers - sends rendered image to window.
         * @sa glfwSwapBuffers()
         * 
         */
        void draw() const;
        /**
         * @brief Is Window open.
         * @sa glfwWindowShouldClose()
         * 
         * @return false If the window closed, or should be closed.
         */
        bool isActive() const;

        /**
         * @brief Get window's title from params object.
         * 
         */
        inline std::string title() const 
            { return m_params.m_title; }
        /**
         * @brief Get window's width from params object.
         * 
         */
        inline int screenWidth() const 
            { return m_params.m_width; }
        /**
         * @brief Get window's height from params object.
         * 
         */
        inline int screenHeight() const 
            { return m_params.m_height; }
        /**
         * @brief Check if window's allowed to resize from params object.
         * 
         */
        inline bool allowResize() const 
            { return m_params.m_allowResize; }
        /**
         * @brief Check if window was initialized.
         * 
         */
        inline bool initialzed() const 
            { return m_window != nullptr; }

        /**
         * @brief Set a Glfw callback for listening for keyboard input.
         * @sa glfwSetKeyCallback()
         */
        void listenForKeyEvents();
        /**
         * @brief Set a Glfw callback for listening for mouse key input.
         * @sa glfwSetMouseButtonCallback()
         */
        void listenForMouseKeyEvents();
        /**
         * @brief Set a Glfw callback for listening for mouse movement input.
         * @sa glfwSetCursorPosCallback()
         */
        void listenForMouseMoveEvents();
        /**
         * @brief Set a Glfw callback for listening for Window specific events (currently only resize).
         * @sa glfwSetFramebufferSizeCallback()
         */
        void listenForWindowResizeEvents();

        void registerKeyCallback(std::function<void(Events::KeyEvent&&)>&& t_callback, 
            std::tuple<Events::KeyEvent::KeyMods, Events::KeyEvent::Key, Events::KeyEvent::KeyEventType>&& t_key)
            { m_keyEventCallbacks[t_key] = std::move(t_callback); }
        void registerMouseKeyCallback(std::function<void(Events::MouseKeyEvent&&)>&& t_callback, 
            std::tuple<Events::MouseKeyEvent::KeyMods, Events::MouseKeyEvent::Key, Events::MouseKeyEvent::KeyEventType>&& t_key)
            { m_mouseKeyEventCallbacks[t_key] = std::move(t_callback); }
        void registerMouseMoveCallback(std::function<void(Events::MouseMoveEvent&&)>&& t_callback)
            { m_mouseMoveEventCallback = std::move(t_callback); }
        void registerWindowCallback(std::function<void(Events::WindowEvent&&)>&& t_callback)
            { m_windowEventCallback = std::move(t_callback); }

    private:
        GLFWwindow *m_window = nullptr;
        std::map<std::tuple<Events::KeyEvent::KeyMods, Events::KeyEvent::Key, Events::KeyEvent::KeyEventType>, std::function<void(Events::KeyEvent&&)>> m_keyEventCallbacks;
        std::map<std::tuple<Events::MouseKeyEvent::KeyMods, Events::MouseKeyEvent::Key, Events::MouseKeyEvent::KeyEventType>, std::function<void(Events::MouseKeyEvent&&)>> m_mouseKeyEventCallbacks;
        std::function<void(Events::MouseMoveEvent&&)> m_mouseMoveEventCallback;
        std::function<void(Events::WindowEvent&&)> m_windowEventCallback;

        std::tuple<double, double> m_lastMousePos;
        bool m_paramsSet = false;
        WindowParams m_params;
    };
}