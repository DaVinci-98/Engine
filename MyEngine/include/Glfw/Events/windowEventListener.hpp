#pragma once

#include "EventSystem/eventListener.hpp"
#include "Glfw/Events/windowEvent.hpp"

namespace MyEngine::Glfw::Events
{
    class WindowEventListener: public EventSystem::EventListener<WindowEvent>
    {

    };
}