#pragma once

#include "EventSystem/event.hpp"
#include "Glfw/Events/keyEvent.hpp"
#include "Glfw/Events/keyEventEmitter.hpp"
#include "Glfw/Events/mouseKeyEvent.hpp"
#include "Glfw/Events/mouseKeyEventEmitter.hpp"
#include "Glfw/Events/mouseMoveEvent.hpp"
#include "Glfw/Events/mouseMoveEventEmitter.hpp"
#include "Glfw/Events/windowEvent.hpp"
#include "Glfw/Events/windowEventEmitter.hpp"

#include <GLFW/glfw3.h>
#include <string>
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
         * @brief Set a Glfw callback for listening for keyboard input.
         * @sa glfwSetKeyCallback()
         * 
         * @return Reference to Events::KeyEventEmitter - to be passed into EventListener's registerEmitter() function.
         */
        Events::KeyEventEmitter& listenForKeyEvents();
        /**
         * @brief Set a Glfw callback for listening for mouse key input.
         * @sa glfwSetMouseButtonCallback()
         * 
         * @return Reference to Events::MouseKeyEventEmitter - to be passed into EventListener's registerEmitter() function.
         */
        Events::MouseKeyEventEmitter& listenForMouseKeyEvents();
        /**
         * @brief Set a Glfw callback for listening for mouse movement input.
         * @sa glfwSetCursorPosCallback()
         * 
         * @return Reference to Events::MouseMoveEventEmitter - to be passed into EventListener's registerEmitter() function.
         */
        Events::MouseMoveEventEmitter& listenForMouseMoveEvents();
        /**
         * @brief Set a Glfw callback for listening for Window specific events (currently only resize).
         * @sa glfwSetFramebufferSizeCallback()
         * 
         * @return Reference to Events::WindowEventEmitter - to be passed into EventListener's registerEmitter() function.
         */
        Events::WindowEventEmitter& listenForWindowResizeEvents();

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

    private:
        GLFWwindow *m_window = nullptr;

        bool m_paramsSet = false;
        WindowParams m_params;
        
        Events::KeyEventEmitter m_keyEventEmitter;
        Events::MouseKeyEventEmitter m_mouseKeyEventEmitter;
        Events::MouseMoveEventEmitter m_mouseMoveEventEmitter;
        Events::WindowEventEmitter m_windowEventEmitter;
    };
}