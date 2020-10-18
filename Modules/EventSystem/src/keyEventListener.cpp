#include "keyEventListener.hpp"

namespace MyEngine::EventSystem
{
    void KeyEventListener::dispatch(KeyEvent&& t_keyEvent)
    {
        unsigned int keyCode = t_keyEvent.keyCode();
        if(m_dispatcher.count(keyCode) == 0) return;
        (m_dispatcher[keyCode])(t_keyEvent);
    }

    bool KeyEventListener::setKeyCallback(unsigned int t_keyCode, std::function<void(KeyEvent&)>&& t_callback)
    {
        if(m_dispatcher.count(t_keyCode) > 0) return false;
        auto pair = std::pair<unsigned int, std::function<void(KeyEvent&)>&&>(t_keyCode, std::move(t_callback));
        m_dispatcher.insert(std::move(pair));
        return true;
    }

    bool KeyEventListener::deleteKeyCallback(unsigned int t_keyCode)
    {
        if(m_dispatcher.count(t_keyCode) == 0) return false;

        m_dispatcher.erase(t_keyCode);
        return true;
    }
}