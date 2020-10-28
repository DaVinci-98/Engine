#pragma once

#include "event.hpp"

namespace MyEngine::Glfw
{
    class MouseKeyEvent: public EventSystem::Event<MouseKeyEvent>
    {

    };
}