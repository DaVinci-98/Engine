#include "eventListener.hpp"

namespace MyEngine::EventSystem
{
    template <class EventType>
    void EventListener<EventType>::dispatch(Event<EventType>& t_event)
    { 
        for( auto[key, callback] : m_callbackMap)
        {
            callback(t_event);
            if(t_event.isHandled()) return;
        }
    }
}