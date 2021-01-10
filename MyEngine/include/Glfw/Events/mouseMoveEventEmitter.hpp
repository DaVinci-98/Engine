#pragma once

#include "EventSystem/eventEmitter.hpp"
#include "Glfw/Events/mouseMoveEvent.hpp"

namespace MyEngine::Glfw::Events
{
    /**
     * @brief Emits MouseMoveEvent objects.
     * 
     */
    class MouseMoveEventEmitter: public EventSystem::EventEmitter<MouseMoveEvent>
    {
    public:
        /**
         * @brief Send a MouseMoveEvent with provided:
         * 
         * @param t_posX current x coordinate
         * @param t_posY current y coordinate
         */
        void sendEvent(double t_posX, double t_posY);
    private:
        double m_lastX = 0;
        double m_lastY = 0;
    };
}