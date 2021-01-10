#pragma once

#include "EventSystem/event.hpp"
#include "EventSystem/eventEmitter.hpp"

#include <unordered_map>
#include <functional>
#include <iostream>

namespace MyEngine::EventSystem
{
    /**
     * @brief Base class used to gather events sent by EventEmitter.
     * 
     * @tparam EventType type of an event to listen to.
     */
    template <class EventType>
    class EventListener
    {
    public:
        /**
         * @brief Basic dispatch function for registering to EventEmitter.
         * Sends event thorugh all of the callbacks.
         * 
         * @param t_event 
         */
        virtual void dispatch(EventType&& t_event)
        {
            for (auto& [t_key, t_callback] : m_callbackMap)
            {
                t_event.dispatched();
                t_callback(t_event);
                if(t_event.isHandled()) return;
            }
        }
        /**
         * @brief Registers callback function under specified key.
         * After EventLister gets an Event it sends it to specified callback.
         * 
         * @param t_key key used to identify which callback the Event be send too.
         * @param t_callback callback for an event.
         */
        void registerCallback(unsigned int t_key, std::function<void(EventType&)>&& t_callback)
        {
            auto pair = std::pair<unsigned int, std::function<void(EventType&)>>(t_key, std::move(t_callback));
            m_callbackMap.insert(std::move(pair)); 
        }
        /**
         * @brief Register dispatch() function to provided EventEmitter
         * 
         * @param t_emitter EventEmitter for Event type.
         */
        inline void registerEmitter(EventEmitter<EventType>& t_emitter)
        {
            auto dispatcher = [this](EventType&& t_event) -> void { this -> dispatch(std::move(t_event)); };
            t_emitter.registerDispatcher(std::move(dispatcher));
        }
        /**
         * @brief Register listener to handle unhandled events.
         * If flag handled of an Event is not set, it will be sent to next listener.
         * 
         * @param t_listner next listener in line.
         */
        inline void registerNextListener(EventListener<EventType>& t_listner)
            { m_nextDispatcher = [&t_listner](EventType&& t_event) -> void { t_listner.dispatch(std::move(t_event)); };}
        /**
         * @brief Remove callback with provided key.
         * 
         */
        inline void deleteCallback(unsigned int t_key)
            { m_callbackMap.erase(t_key); }
        /**
         * @brief Remove next listener.
         * 
         */
        inline void deleteNextListener()
            { m_nextDispatcher = nullptr; }
        /**
         * @brief Get a refernce to a callback with provided key.
         * 
         * @param t_key key of the callback.
         * @return std::function with void return type, taking reference to Event with type EventType.
         */
        inline std::function<void(EventType&)>& callback(unsigned int t_key)
            { return m_callbackMap[t_key]; }
        /**
         * @brief Return a reference to the dispatch() function of next listener.
         * 
         * @return std::function with void return type, taking rvalue reference to Event with type EventType.
         */
        inline std::function<void(EventType&&)>& nextDispatcher()
            { return m_nextDispatcher;}

    protected:
        std::function<void(EventType&&)> m_nextDispatcher;
        std::unordered_map<unsigned int, std::function<void(EventType&)>> m_callbackMap;
    };
}