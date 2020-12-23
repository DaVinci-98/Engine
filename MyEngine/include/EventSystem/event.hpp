#pragma once

#include "Helpers/type.hpp"

#include <string>

namespace MyEngine::EventSystem
{
    extern void logUnhandled(std::string&& t_type);

    template <class Derived>
    class Event
    {
    public:
        ~Event() { if(!m_handled && m_dispatched) logUnhandled(Event<Derived>::typeName()); }
        inline void handle() { m_handled = true; }
        inline void setDispatched() { m_dispatched = true; }
        inline bool isHandled() const { return m_handled; }
        static std::string typeName() { return Helpers::getTypeName<Derived>(); }

    protected:
        Event() { }

    private:
        bool m_handled = false;
        bool m_dispatched = false;
    };
}