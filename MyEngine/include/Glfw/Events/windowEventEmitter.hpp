#pragma once

#include "EventSystem/eventEmitter.hpp"
#include "Glfw/Events/windowEvent.hpp"

namespace MyEngine::Glfw::Events
{
    class WindowEventEmitter: public EventSystem::EventEmitter<WindowEvent>
    {

    };
}