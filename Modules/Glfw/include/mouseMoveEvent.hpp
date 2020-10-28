#pragma once

#include "event.hpp"

namespace MyEngine::Glfw
{
    class MouseMoveEvent: public EventSystem::Event<MouseMoveEvent>
    {

    };
}