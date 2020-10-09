#pragma once

#include "event/event.hpp"

namespace MyEngine
{
    class MouseKeyEvent: public Event
    {
    public:
        MouseKeyEvent()
            : Event(EventType::mouseKeyEvent) { }
    };
}