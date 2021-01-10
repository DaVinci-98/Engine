#pragma once

#include "EventSystem/event.hpp"
#include "Renderer/drawable2D.hpp"

#include <functional>

namespace MyEngine::Renderer::Events
{
    /**
     * @brief Event sent to initiate rendering.
     * 
     */
    class DrawableAddEvent: public EventSystem::Event<DrawableAddEvent>
    {
    public:
        /**
         * @brief Construct a new DrawableAddEvent object.
         * 
         * @param t_drawable Object which will be drawn.
         * @param t_callback Function to call before drawing the object.
         */
        DrawableAddEvent(std::shared_ptr<Drawable2D>& t_drawable, std::function<void(void)>&& t_callback):
            m_drawable(t_drawable), m_callback(t_callback) { }    
                
        /**
         * @brief Calls the stored callback.
         * 
         */
        inline void callback()
            { if(m_callback) m_callback(); }

        /**
         * @brief Returns the stored drawable.
         * 
         */
        inline std::shared_ptr<Drawable2D> drawable()
            { return m_drawable; }
    private:
        std::shared_ptr<Drawable2D> m_drawable;
        std::function<void(void)> m_callback;
    };
}