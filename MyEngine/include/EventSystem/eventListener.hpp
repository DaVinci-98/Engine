#pragma once

#include "EventSystem/event.hpp"
#include "EventSystem/eventEmitter.hpp"

#include <unordered_map>
#include <functional>
#include <iostream>

namespace MyEngine::EventSystem
{
    template <class EventType>
    class EventListener
    {
    public:
        virtual void dispatch(EventType&& t_event) = 0;
        inline void registerNextListener(EventListener<EventType>& t_listner)
        {
            m_nextDispatcher = [&t_listner](EventType&& t_event) -> void { t_listner -> dispatch(std::move(t_event)); };
        }
        inline void registerEmitter(EventEmitter<EventType>& t_emitter)
        {
            auto dispatcher = [this](EventType&& t_event) -> void { this -> dispatch(std::move(t_event)); };
            t_emitter.registerDispatcher(std::move(dispatcher));
        }
        inline void deleteCallback(unsigned int t_key)
        { 
            m_callbackMap.erase(t_key); 
        }
    protected:
        EventListener() { }
        void registerCallback(unsigned int t_key, std::function<void(EventType&)>&& t_callback)
        {
            auto pair = std::pair<unsigned int, std::function<void(EventType&)>>(t_key, std::move(t_callback));
            m_callbackMap.insert(std::move(pair)); 
        }
        inline std::function<void(EventType&)>& callback(unsigned int t_key)
        { 
            return m_callbackMap[t_key]; 
        }
        inline std::function<void(EventType&&)>& nextDispatcher()
        { 
            return m_nextDispatcher;
        }
    private:
        std::function<void(EventType&&)> m_nextDispatcher;
        std::unordered_map<unsigned int, std::function<void(EventType&)>> m_callbackMap;
    };
}