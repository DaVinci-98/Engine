#pragma once

#include "event/event.hpp"

namespace MyEngine
{
    class MouseMoveEvent: public Event
    {
    public:
        MouseMoveEvent()
            : Event(EventType::mouseMoveEvent) { }
    };
}