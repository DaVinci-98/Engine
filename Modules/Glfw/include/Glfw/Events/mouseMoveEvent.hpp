#pragma once

namespace MyEngine::Glfw::Events
{
    /**
     * @brief Event for sending information about mouse position.
     * 
     */
    class MouseMoveEvent
    {
    public:
        /**
         * @brief Construct a new Mouse Move Event object.
         * 
         * @param t_xPos current x coordinate.
         * @param t_yPos current y coordinate.
         * @param t_xVec change from last position in x axis.
         * @param t_yVec change from last position in y axis.
         */
        MouseMoveEvent(double t_xPos, double t_yPos, double t_xVec, double t_yVec):
            m_xPos(t_xPos), m_yPos(t_yPos), m_xVec(t_xVec), m_yVec(t_yVec) { }

        /**
         * @brief Get mouse position.
         * 
         * @return std::touple of double, double - mouse position.
         */
        inline auto pos() const { return m_xPos, m_yPos; }
        /**
         * @brief Get mouse movement from last position.
         * 
         * @return std::touple of double, double - movement from last position.
         */
        inline auto vec() const { return m_xVec, m_yVec; }

    private:
        double m_xPos;
        double m_yPos;
        double m_xVec;
        double m_yVec;
    };
}