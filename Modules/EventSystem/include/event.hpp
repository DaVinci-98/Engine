#pragma once

namespace MyEngine::EventSystem
{
    class Event
    {
    public:
        enum EventType
        {
            keyEvent,
            mouseMoveEvent,
            mouseKeyEvent
        };

        Event(EventType t_eventType)
            : m_eventType(t_eventType) { }
            
        EventType eventType() const { return m_eventType; }
        void handle() { m_handled = true; }
        bool isHandled() const { return m_handled; }

    private:
        EventType m_eventType;
        bool m_handled;
    };
}