#pragma once

#include "Renderer/drawable2D.hpp"

#include <memory>
#include <queue>
#include <unordered_map>

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
        static bool draw(Drawable2D& t_drawable);
        static bool draw(std::vector<Drawable2D>& t_drawables);

        void resizeWindow(int t_width, int t_height);
        void setOrtho2D(int t_widt, int t_height);

        std::string colourShader();
        std::string textureShader();
        inline std::shared_ptr<Shader>& shader(std::string& t_name)
            { return m_activeShaders[t_name]; }

        inline glm::mat4& projection() 
            { return m_projection; }
    private:
        static bool draw(unsigned int t_count);

        std::unordered_map<std::string, std::shared_ptr<Shader>> m_activeShaders;
        glm::mat4 m_projection = glm::mat4(1);
        glm::mat4 m_view = glm::mat4(1);
    };
}