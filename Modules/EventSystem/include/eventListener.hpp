#pragma once

#include "event.hpp"

#include <unordered_map>
#include <functional>

namespace MyEngine::EventSystem
{
    template <class EventType>
    class EventListener
    {
    public:
        inline void registerCallback(unsigned int t_key, std::function<void(Event<EventType>&)>&& t_callback)
            { m_callbackMap.insert(t_key, std::move(t_callback)); }
        void dispatch(Event<EventType>& t_event);
        inline void deleteCallback(unsigned int t_key)
            { m_callbackMap.erase(t_key); }
    protected:
        EventListener() { }
        inline std::function<void(Event<EventType>&)>& callback(unsigned int t_key)
            { return m_callbackMap[t_key]; }
    private:
        std::unordered_map<unsigned int, std::function<void(Event<EventType>&)>> m_callbackMap;
    };
}