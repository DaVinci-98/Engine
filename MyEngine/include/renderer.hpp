#pragma once

#include "object.hpp"
#include <memory>

namespace MyEngine
{
    // Responsible for rendering.
    class Renderer
    {
    public:
        Renderer() { };
        ~Renderer() { };
        // Clear the window.
        void clear() const;
        // Draw a t_object usign Model-View-Projection matrix t_MVP.
        void draw(Object& t_object, glm::mat4& t_MVP);
    };
}