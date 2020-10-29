#pragma once

#include "EventSystem/event.hpp"

namespace MyEngine::Glfw
{
    class MouseMoveEvent: public EventSystem::Event<MouseMoveEvent>
    {

    };
}