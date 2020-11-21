#pragma once

#include "EventSystem/eventListener.hpp"
#include "Glfw/Events/windowEvent.hpp"

namespace MyEngine::Glfw::Events
{
    class WindowEventListener: public EventSystem::EventListener<WindowEvent>
    {
    public:
        virtual void dispatch(WindowEvent&& t_keyEvent) override;
        void registerResizeCallback(std::function<void(WindowEvent&)>&& t_callback);
    };
}