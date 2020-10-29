#pragma once

#include <typeinfo>

namespace MyEngine::EventSystem
{
    template <class Derived>
    class Event
    {
    public:
        inline void handle() { m_handled = true; }
        inline bool isHandled() const { return m_handled; }
        static inline auto type() { return typeid(Derived); }

    protected:
        Event() { }

    private:
        bool m_handled;
    };
}