#pragma once

#include "keyEvent.hpp"
#include "eventListener.hpp"

#include <unordered_map>
#include <functional>

namespace MyEngine::Glfw
{
    class KeyEventListener: public EventSystem::EventListener<KeyEvent>
    {
    public:
        void dispatch(KeyEvent& t_keyEvent);
    };
} 
