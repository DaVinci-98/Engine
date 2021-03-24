#pragma once

#include "EventSystem/event.hpp"

#include <functional>

namespace MyEngine::EventSystem
{
    /**
     * @brief Base class used to send Events.
     * 
     * @tparam EventType type of Event which can bes sent by this class.
     */
    template <class EventType>
    class EventEmitter
    {
    public:
        /**
         * @brief Register function, which will be used for sending Events.
         * Usually function will be dispatch() from EventListener.
         * 
         * @param t_dispatcher registered function, gets the event as rvalue.
         * 
         */
        inline void registerDispatcher(std::function<void(EventType &&)>&& t_dispatcher)
            { m_dispatcher = t_dispatcher; }
        /**
         * @brief Sends the Event using registered dispatcher function.
         * 
         * @param t_event rvalue reference to the Event
         */
        inline void sendEvent(EventType&& t_event)
        { m_dispatcher(std::move(t_event)); }

    private:
        std::function<void(EventType &&)> m_dispatcher;
    };
}