#pragma once

#include "event.hpp"
#include "eventListener.hpp"
#include "eventEmitter.hpp"

#include <functional>
#include <vector>

namespace MyEngine::EventSystem
{
    template <class EventType>
    class EventManager
    {
    public:
        void registerEmitter(EventEmitter<EventType>& t_emitter);
        inline void registerListener(EventListener<EventType>&& t_listener)
            { m_listeners.push_back(std::move(t_listener)); }
    private:
        void dispatch(Event<EventType>&& t_event);
        std::vector<EventListener<EventType>> m_listeners;
    };
}