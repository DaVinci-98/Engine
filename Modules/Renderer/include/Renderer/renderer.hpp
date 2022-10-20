#pragma once

#include "Renderer/drawable2D.hpp"

#include <memory>
#include <map>

namespace MyEngine::Renderer
{
    /**
     * @brief Responsible for rendering Drawable2D objects.
     * 
     */
    class Renderer
    {
    public:
        /**
         * @brief Initialize Glad with current glfw context.
         * Also sets up blending in openGL.
         * 
         * @return true if initialization was successful
         * 
         */
        bool initialize();

        /**
         * @brief Clear the rendering buffer.
         * 
         * @return true if operation was successful
         */
        bool clear() const;
        /**
         * @brief Draw provided drawable to the buffer.
         * 
         * @param t_drawable drawble object to draw.
         * @return true if operation was successful
         */
        bool draw(Drawable2D& t_drawable);

        /**
         * @brief Resize the glfw window.
         * 
         * @param t_width width of the new window
         * @param t_height height of the new window
         */
        void resizeWindow(int t_width, int t_height);
        /**
         * @brief Set the projection martix to orthographic projection with provided height and width.
         * 
         */
        void setOrtho2D(int t_width, int t_height);

        /**
         * @brief Initialize a colour shader and return a string for accessing it from renderer.
         * Colour shader renders meshes with flat colour.
         * (Accessing shaders from within renderer makes binding projection matrices easier)
         * 
         */
        std::string colourShader();
        /**
         * @brief Initialize a texture shader and return a string for accessing it from renderer.
         * Texture shader renders meshes with bound texture.
         * (Accessing shaders from within renderer makes binding projection matrices easier)
         * 
         */
        std::string textureShader();
        /**
         * @brief Get a shared pointer to a Renderer::Shader with provided name.
         * 
         * @sa colourShader()
         * @sa textureShader()
         * 
         */
        inline std::shared_ptr<Shader> shader(std::string const& t_name)
            { return m_activeShaders[t_name]; }
        /**
         * @brief Get a shared pointer to a Renderer::Shader with provided name.
         * 
         * @sa colourShader()
         * @sa textureShader()
         * 
         */
        inline std::shared_ptr<Shader> shader(std::string && t_name)
            { return m_activeShaders[t_name]; }

        /**
         * @brief Returns a reference to projection matrix.
         * 
         */
        inline glm::mat4& projection() 
            { return m_projection; }

    private:
        bool draw(unsigned int t_count);

        std::shared_ptr<Material> m_lastMaterial;
        std::map<std::string, std::shared_ptr<Shader>> m_activeShaders;
        glm::mat4 m_projection = glm::mat4(1);
        glm::mat4 m_view = glm::mat4(1);
    };
}