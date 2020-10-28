#include "eventManager.hpp"

namespace MyEngine::EventSystem
{
    template <class EventType>
    void EventManager<EventType>::registerEmitter(EventEmitter<EventType>& t_emitter)
    {
        auto dispatcher = [this](Event<EventType>&& t_event) -> void { this -> dispatch(t_event); };
        t_emitter.registerDispatcher(dispatcher);
    }

    template <class EventType>
    void EventManager<EventType>::dispatch(Event<EventType>&& t_event)
    {
        for (auto listener : m_listeners)
        {
            listener.dispatch(t_event);
            if(t_event.isHandled()) return;
        }
    }
}