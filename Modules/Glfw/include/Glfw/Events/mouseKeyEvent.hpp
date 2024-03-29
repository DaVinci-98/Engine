#pragma once

#include <tuple>

namespace MyEngine::Glfw::Events
{
    /**
     * @brief Event for sending information about mouse key input.
     * 
     */
    class MouseKeyEvent
    {
    public:
        /**
         * @brief Action which caused MouseKeyEvent to be emitted.
         * 
         */
        enum KeyEventType
        {
            PRESSED = 1, 
            RELEASED = 0, 
        };

        /**
         * @brief Modificators which were present when MouseKeyEvent was emitted.
         * 
         */
        enum KeyMods
        {
            NONE = 0,
            SHIFT,
            CONTROL, 
            CONTROL_SHIFT,
            ALT,
            ALT_SHIFT,
            ALT_CONTROL,
            ALT_CONTROL_SHIFT,
            SUPER,
            SUPER_SHIFT,
            SUPER_CONTROL,
            SUPER_CONTROL_SHIFT,
            SUPER_ALT,
            SUPER_ALT_SHIFT,
            SUPER_ALT_CONTROL,
            SUPER_ALT_CONTROL_SHIFT,
            CAPS_LOCK,
            CAPS_LOCK_SHIFT,
            CAPS_LOCK_CONTROL, 
            CAPS_LOCK_CONTROL_SHIFT,
            CAPS_LOCK_ALT,
            CAPS_LOCK_ALT_SHIFT,
            CAPS_LOCK_ALT_CONTROL,
            CAPS_LOCK_ALT_CONTROL_SHIFT,
            CAPS_LOCK_SUPER,
            CAPS_LOCK_SUPER_SHIFT,
            CAPS_LOCK_SUPER_CONTROL,
            CAPS_LOCK_SUPER_CONTROL_SHIFT,
            CAPS_LOCK_SUPER_ALT,
            CAPS_LOCK_SUPER_ALT_SHIFT,
            CAPS_LOCK_SUPER_ALT_CONTROL,
            CAPS_LOCK_SUPER_ALT_CONTROL_SHIFT,  
            NUM_LOCK,
            NUM_LOCK_SHIFT,
            NUM_LOCK_CONTROL, 
            NUM_LOCK_CONTROL_SHIFT,
            NUM_LOCK_ALT,
            NUM_LOCK_ALT_SHIFT,
            NUM_LOCK_ALT_CONTROL,
            NUM_LOCK_ALT_CONTROL_SHIFT,
            NUM_LOCK_SUPER,
            NUM_LOCK_SUPER_SHIFT,
            NUM_LOCK_SUPER_CONTROL,
            NUM_LOCK_SUPER_CONTROL_SHIFT,
            NUM_LOCK_SUPER_ALT,
            NUM_LOCK_SUPER_ALT_SHIFT,
            NUM_LOCK_SUPER_ALT_CONTROL,
            NUM_LOCK_SUPER_ALT_CONTROL_SHIFT,
            NUM_LOCK_CAPS_LOCK,
            NUM_LOCK_CAPS_LOCK_SHIFT,
            NUM_LOCK_CAPS_LOCK_CONTROL, 
            NUM_LOCK_CAPS_LOCK_CONTROL_SHIFT,
            NUM_LOCK_CAPS_LOCK_ALT,
            NUM_LOCK_CAPS_LOCK_ALT_SHIFT,
            NUM_LOCK_CAPS_LOCK_ALT_CONTROL,
            NUM_LOCK_CAPS_LOCK_ALT_CONTROL_SHIFT,
            NUM_LOCK_CAPS_LOCK_SUPER,
            NUM_LOCK_CAPS_LOCK_SUPER_SHIFT,
            NUM_LOCK_CAPS_LOCK_SUPER_CONTROL,
            NUM_LOCK_CAPS_LOCK_SUPER_CONTROL_SHIFT,
            NUM_LOCK_CAPS_LOCK_SUPER_ALT,
            NUM_LOCK_CAPS_LOCK_SUPER_ALT_SHIFT,
            NUM_LOCK_CAPS_LOCK_SUPER_ALT_CONTROL,
            NUM_LOCK_CAPS_LOCK_SUPER_ALT_CONTROL_SHIFT, 
        };

        /**
         * @brief Key which caused MouseKeyEvent to be emitted.
         * 
         */
        enum Key
        {
            MOUSE_BUTTON_1 = 0,
            MOUSE_BUTTON_2 = 1,
            MOUSE_BUTTON_3 = 2,
            MOUSE_BUTTON_4 = 3,
            MOUSE_BUTTON_5 = 4,
            MOUSE_BUTTON_6 = 5,
            MOUSE_BUTTON_7 = 6,
            MOUSE_BUTTON_8 = 7,
            MOUSE_BUTTON_LAST = MOUSE_BUTTON_8,
            MOUSE_BUTTON_LEFT = MOUSE_BUTTON_1,
            MOUSE_BUTTON_RIGHT = MOUSE_BUTTON_2,
            MOUSE_BUTTON_MIDDLE = MOUSE_BUTTON_3
        };

        MouseKeyEvent(std::tuple<KeyMods, Key, KeyEventType>&& t_key, double t_xPos, double t_yPos):
            m_xPos(t_xPos), m_yPos(t_yPos) { std::tie(m_mods, m_key, m_keyEventType) = t_key; }
        MouseKeyEvent(KeyMods t_mods, Key t_key, KeyEventType t_keyEventType, double t_xPos, double t_yPos):
            m_mods(t_mods), m_key(t_key), m_keyEventType(t_keyEventType), m_xPos(t_xPos), m_yPos(t_yPos) { }

        inline std::tuple<KeyMods, Key, KeyEventType> getEventDesc() 
            { return std::make_tuple(m_mods, m_key, m_keyEventType); }
        /**
         * @brief Get mouse postion.
         * 
         * @return std::tuple of double, double - x,y coordinates.
         */
        inline std::tuple<double, double> pos() const
             { return std::make_tuple(m_xPos, m_yPos); }

    private:
        KeyMods m_mods;
        Key m_key;
        KeyEventType m_keyEventType;
        double m_xPos;
        double m_yPos;
    };
}