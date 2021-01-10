#include "Glfw/Events/mouseKeyEvent.hpp"

namespace MyEngine::Glfw::Events
{
    unsigned int MouseKeyEvent::getKeyCode(KeyMods t_mods, Key t_key, KeyEventType t_keyEventType)
    {
        unsigned int keyCode = 0;

        keyCode |= t_key;
        keyCode = keyCode << 8;

        keyCode |= t_mods;
        keyCode = keyCode << 8;

        keyCode |= t_keyEventType;

        return keyCode;
    }

    bool MouseKeyEvent::checkKeyEventType(KeyEventType t_keyEventType) const
    {
        unsigned int keyEventType = (m_keyCode & 0x000000ff);
        return KeyEventType(keyEventType) == t_keyEventType;
    }

    bool MouseKeyEvent::checkKeyMod(KeyMods t_keyMod) const
    {
        unsigned int mods = (m_keyCode & 0x0000ff00) >> 8;
        return (KeyMods(mods) & t_keyMod) != 0;
    }

    bool MouseKeyEvent::checkKey(Key t_key) const
    {
        unsigned int key = (m_keyCode & 0xffff0000) >> 16;
        return Key(key) == t_key;
    }
}