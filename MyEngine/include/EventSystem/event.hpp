#pragma once

namespace MyEngine::EventSystem
{
    /**
     * @brief Base class used for internal communication.
     * 
     * @tparam Derived - class deriving from the Event. 
     * 
     */
    template <class Derived>
    class Event
    {
    public:
        /**
         * @brief Set handled flag.
         * 
         */
        inline void handle() 
            { m_handled = true; }
        /**
         * @brief Set dispatched flag.
         * 
         */
        inline void dispatched() 
            { m_dispatched = true; }
        /**
         * @brief Check if handled flag is set.
         * 
         */
        inline bool isHandled() const 
            { return m_handled; }
        /**
         * @brief Check if dispatched flag is set.
         * 
         */
        inline bool isDispatched() const 
            { return m_dispatched; }

    protected:
        Event() { }

    private:
        bool m_handled = false;
        bool m_dispatched = false;
    };
}