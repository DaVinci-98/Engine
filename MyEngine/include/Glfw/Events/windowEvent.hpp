#pragma once

#include "EventSystem/event.hpp"

namespace MyEngine::Glfw::Events
{
    class WindowEvent: public EventSystem::Event<WindowEvent>
    {

    };
}