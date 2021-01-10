#include "Renderer/Events/drawableAddEventListener.hpp"

namespace MyEngine::Renderer::Events
{
    void DrawableAddEventListener::dispatch(DrawableAddEvent&& t_event)
    {
        if(!m_nextDispatcher)
            m_events.push_back(std::move(t_event));
        else
        {
            m_events.push_back(t_event);
            nextDispatcher()(std::move(t_event));
        }
    }
}