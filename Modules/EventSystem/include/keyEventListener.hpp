#pragma once

#include "keyEvent.hpp"

#include <unordered_map>
#include <functional>

namespace MyEngine::EventSystem
{
    class KeyEventListener
    {
    public:
        void dispatch(KeyEvent&& t_keyEvent);
        bool setKeyCallback(unsigned int t_keyCode, std::function<void(KeyEvent&)>&& t_callback);
        bool deleteKeyCallback(unsigned int t_keyCode);

        bool isListening() const { return m_listening; }
        void setListening() { m_listening = true; }
    private:
        bool m_listening = false;
        std::unordered_map<unsigned int, std::function<void(KeyEvent&)>> m_dispatcher;
    };
} 
