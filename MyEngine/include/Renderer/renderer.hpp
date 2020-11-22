#pragma once

#include "Renderer/object.hpp"

#include <memory>

namespace MyEngine::Renderer
{
    // Responsible for rendering.
    class Renderer
    {
    public:
        Renderer() { };
        ~Renderer() { };
        bool initialize();

        bool clear() const;
        bool draw(Object& t_object, glm::mat4& t_MVP);

        void resizeWindow(int t_width, int t_height);
        void setOrtho2D(int t_widt, int t_height);

        inline glm::mat4& projection() { return m_projection; }
    private:
        glm::mat4 m_projection = glm::mat4(1);
    };
}