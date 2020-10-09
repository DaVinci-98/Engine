#include "event/keyEvent.hpp"

namespace MyEngine
{
    unsigned int KeyEvent::getKeyCode(KeyMods& t_mods, Key& t_key, KeyEventType& t_keyEventType)
    {
        unsigned int keyCode = 0;

        keyCode |= t_key;
        keyCode = keyCode << 8;

        keyCode |= t_mods;
        keyCode = keyCode << 8;

        keyCode |= static_cast<unsigned int>(t_keyEventType);

        return keyCode;
    }

    bool KeyEvent::checkKeyEventType(KeyEventType& t_keyEventType) const
    {
        unsigned int keyEventType = (m_keyCode & 0x000000ff);
        return KeyEventType(keyEventType) == t_keyEventType;
    }

    bool KeyEvent::ckeckKeyMod(KeyMods& t_keyMods) const
    {
        unsigned int mods = (m_keyCode & 0x0000ff00) >> 8;
        return (KeyMods(mods) & t_keyMods) != 0;
    }

    bool KeyEvent::checkKey(Key& t_key) const
    {
        unsigned int key = (m_keyCode & 0xffff0000) >> 16;
        return Key(key) == t_key;
    }
}