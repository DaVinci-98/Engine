#pragma once

#include "event.hpp"

namespace MyEngine::EventSystem
{
    class MouseKeyEvent: public Event
    {
    public:
        MouseKeyEvent()
            : Event(EventType::mouseKeyEvent) { }
    };
}