#pragma once

#include "EventSystem/event.hpp"

namespace MyEngine::Glfw::Events
{
    class MouseKeyEvent: public EventSystem::Event<MouseKeyEvent>
    {

    };
}