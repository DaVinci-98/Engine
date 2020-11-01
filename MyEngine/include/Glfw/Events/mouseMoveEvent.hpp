#pragma once

#include "EventSystem/event.hpp"

namespace MyEngine::Glfw::Events
{
    class MouseMoveEvent: public EventSystem::Event<MouseMoveEvent>
    {

    };
}