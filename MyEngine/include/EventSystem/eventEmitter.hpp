#pragma once

#include "EventSystem/event.hpp"

#include <functional>

namespace MyEngine::EventSystem
{
    template <class EventType>
    class EventEmitter
    {
    public:
        inline void registerDispatcher(std::function<void(EventType &&)>&& t_dispatcher)
            { m_dispatcher = t_dispatcher; }
        inline void sendEvent(EventType&& t_event)
            { m_dispatcher(std::move(t_event)); }

    protected:
        EventEmitter() { }

    private:
        std::function<void(EventType &&)> m_dispatcher;
    };
}