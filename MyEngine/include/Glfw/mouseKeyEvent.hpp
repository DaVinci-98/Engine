#pragma once

#include "EventSystem/event.hpp"

namespace MyEngine::Glfw
{
    class MouseKeyEvent: public EventSystem::Event<MouseKeyEvent>
    {

    };
}