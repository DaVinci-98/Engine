#pragma once

#include "event.hpp"

namespace MyEngine::EventSystem
{
    class MouseMoveEvent: public Event
    {
    public:
        MouseMoveEvent()
            : Event(EventType::mouseMoveEvent) { }
    };
}