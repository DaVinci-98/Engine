#include "keyEventListener.hpp"

namespace MyEngine::Glfw
{
    void KeyEventListener::dispatch(KeyEvent& t_keyEvent)
    {
        unsigned int keyCode = t_keyEvent.keyCode();
        callback(keyCode)(t_keyEvent);
    }
}