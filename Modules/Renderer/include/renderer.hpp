#pragma once

#include "object.hpp"
#include <memory>

namespace MyEngine::Renderer
{
    // Responsible for rendering.
    class Renderer
    {
    public:
        Renderer() { };
        ~Renderer() { };
        // Clear the window.
        bool clear() const;
        // Draw a t_object usign Model-View-Projection matrix t_MVP.
        bool draw(Object& t_object, glm::mat4& t_MVP);
    };
}