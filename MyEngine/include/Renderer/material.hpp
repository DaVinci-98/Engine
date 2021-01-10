#pragma once

#include "Renderer/triangle2D.hpp"
#include "Renderer/shader.hpp"
#include "OpenGL/texture.hpp"
#include "OpenGL/shader.hpp"
#include "OpenGL/indexBuffer.hpp"
#include "OpenGL/vertexBuffer.hpp"
#include "OpenGL/vertexBufferLayout.hpp"

#include <memory>
#include <vector>
#include <map>

namespace MyEngine::Renderer
{
    /**
     * @brief Material class responsible for how triangles in Mesh are rendered.
     * 
     */
    class Material
    {
    public:
        /**
         * @brief Construct a new Material object which uses a provided shader.
         * 
         */
        Material(std::shared_ptr<Shader> t_shader);
        /**
         * @brief Destroy the Material object.
         * 
         */
        ~Material();

        /**
         * @brief Create a texture for this material.
         * 
         * @param t_vertices vertices which will be mapped onto texture.
         * @param t_indicies indicies which will create triangles from provided indicies 
         * that are mapped from texture onto rendered triangles.
         * @param t_path path to the texture file
         * @param t_stride number of floats used by vertex in the buffer.
         * @return unsigned int - slot under which assigned texture will be bound.
         */
        unsigned int setTextureBuffer(std::vector<float> && t_vertices, std::vector<unsigned int> && t_indicies, std::string t_path, unsigned int t_stride);
        /**
         * @brief Set a colour for triangles to be rendered with.
         * 
         * @param t_colour [R,G,B,A] vector representing the colour
         */
        void setColour(glm::vec4&& t_colour);
        /**
         * @brief Create a texture for this material.
         * 
         * @param t_triangles triangles that will be maped from texture onto rendered triangles
         * @param t_path path to the texture file
         * @return unsigned int - slot under which assigned texture will be bound.
         */
        unsigned int setTexture(std::vector<Triangle2D> && t_triangles, std::string t_path);

        /**
         * @brief Create a texture for this material.
         * 
         * @param t_vertices vertices which will be mapped onto texture.
         * @param t_indicies indicies which will create triangles from provided indicies 
         * that are mapped from texture onto rendered triangles.
         * @param t_path path to the texture file
         * @param t_stride number of floats used by vertex in the buffer.
         * @return unsigned int - slot under which assigned texture will be bound.
         */
        inline unsigned int setTextureBuffer(std::vector<float> const& t_vertices, std::vector<unsigned int> const& t_indicies, std::string& t_path, unsigned int t_stride)
            { return setTextureBuffer(std::vector<float>(t_vertices), std::vector<unsigned int>(t_indicies), t_path, t_stride); }
        /**
         * @brief Create a texture for this material.
         * 
         * @param t_triangles triangles that will be maped from texture onto rendered triangles
         * @param t_path path to the texture file
         * @return unsigned int - slot under which assigned texture will be bound.
         */
        inline void setColour(glm::vec4 const& t_colour)
            { setColour(glm::vec4(t_colour)); }
        /**
         * @brief Create a texture for this material.
         * 
         * @param t_triangles triangles that will be maped from texture onto rendered triangles
         * @param t_path path to the texture file
         * @return unsigned int - slot under which assigned texture will be bound.
         */
        inline unsigned int setTexture(std::vector<Triangle2D> const& t_triangles, std::string& t_path)
            { return setTexture(std::vector<Triangle2D>(t_triangles), t_path); }

        /**
         * @brief Get a shared pointer to underlying Renderer::Shader object.
         * 
         */
        inline std::shared_ptr<Shader> shader()
            { return m_shader; }
        /**
         * @brief Get a reference to underlying vector of indicies for this material.
         * (only used for mapping textures)
         * 
         */
        inline std::vector<unsigned int>& indicies()
            { return m_indicies; }
        /**
         * @brief Get a reference to underlying vector of vertices for this material.
         * (only used for mapping textures)
         * 
         */
        inline OpenGL::VertexBuffer& buffer()
            {return *m_vertexBuffer; }
        /**
         * @brief Get a reference to underlying VertexBufferLayout for this material.
         * (only used for mapping textures)
         * 
         */
        inline OpenGL::VertexBufferLayout& layout()
            { return *m_layout; }
        /**
         * @brief Get a number of floats used by vertex in the buffer.
         * 
         */
        inline unsigned int vertexSize() const
            { return m_stride; } 
        /**
         * @brief Returns true if this material renders traingles with textures.
         * 
         */
        inline bool isTexture() const
            { return m_shader->usesTexture(); }
        /**
         * @brief Returns true if this material renders traingles with flat colour.
         * 
         */
        inline bool isColour()
            { return !m_shader->usesTexture(); }   

        /**
         * @brief Bind the underlying shader and uniforms.
         * 
         */
        void bind();

        /**
         * @brief Unbind the underlying shader and uniforms.
         * 
         */
        void unbind();

    private:
        void clear();
        void insertVertex(std::vector<float>&& t_vertex, bool t_useIndicies);
        void insertTriangles(std::vector<Triangle2D>&& t_trinagles, bool t_useIndicies);
        int  findVertex(std::vector<float>& t_vertex);

        unsigned int m_stride = 0;
        bool m_bound = false;

        std::vector<float> m_vertices;
        std::vector<unsigned int> m_indicies;

        std::unique_ptr<OpenGL::Texture> m_texture;
        std::unique_ptr<OpenGL::VertexBuffer> m_vertexBuffer;
        std::unique_ptr<OpenGL::VertexBufferLayout> m_layout;

        std::shared_ptr<Shader> m_shader;
    };
}