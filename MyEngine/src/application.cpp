#include "glad/glad.h"

#include "application.hpp"
#include "indexBuffer.hpp"
#include "vertexBuffer.hpp"
#include "vertexArray.hpp"
#include "shader.hpp"
#include "glException.hpp"
#include "renderer.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <iostream>
#include <stdexcept>
#include <exception>
#include <string>

namespace MyEngine
{
    Application::Application(std::string& t_title, int t_w, int t_h)
    {
        WindowParams params;
        params.m_title = t_title;
        params.m_screenWidth = t_w;
        params.m_screenHeight = t_h;

        params.m_eventCallback = [&](EventSystem::Event&& t_event) -> void
        {
            this->onEvent(std::move(t_event));
        };

        m_window.setParams(std::move(params));
    }

    void Application::onEvent(EventSystem::Event&& t_event)
    {
        switch(t_event.eventType())
        {
            case EventSystem::Event::EventType::keyEvent:
                EventSystem::KeyEvent& keyEvent = static_cast<EventSystem::KeyEvent&>(t_event);
                m_keyEventListener.dispatch(std::move(keyEvent));
                break;
        }
    }

    void Application::setKeyCallback(std::function<void(EventSystem::KeyEvent&)>&& t_callback, 
            EventSystem::KeyEvent::Key t_key, 
            EventSystem::KeyEvent::KeyEventType t_keyEventType, 
            EventSystem::KeyEvent::KeyMods t_mods)
    {
        if(!m_keyEventListener.isListening())
        {
            m_window.listenForKeyEvents();
            m_keyEventListener.setListening();
        }
        unsigned int keyCode = EventSystem::KeyEvent::getKeyCode(t_mods, t_key, t_keyEventType);
        m_keyEventListener.setKeyCallback(keyCode, std::move(t_callback));
    }

    int Application::initialize()
    {
        if(!m_window.initializeWindow())
        {
            return -1;
        }

        if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) 
        {
            return -1;
        }

        GL_CALL(glEnable(GL_BLEND));
        GL_CALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        std::cout << "[VERSION] : " <<  glGetString(GL_VERSION) << std::endl;

        return 0;
    }

    void Application::startLoop()
    {
        bool start = onLoopStart();
        if(!start)
        {
            onLoopEnd();
            return;
        }
        while (m_window.isActive())
        {
            bool frame = onLoop();
            if(!frame)
            {
                onLoopEnd();
                return;
            }

            m_window.draw();
            m_window.pollEvents();
        }
        bool end = onLoopEnd();
        return;
    }
}
