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
    class Material
    {
    public:
        Material(std::shared_ptr<Shader> t_shader):
            m_shader(t_shader) { }

        unsigned int setTextureBuffer(std::vector<float> && t_vertices, std::vector<unsigned int> && t_indecies, std::string t_path, unsigned int t_stride);
        void setColour(glm::vec4&& t_colour);
        unsigned int setTexture(std::vector<Triangle2D> && t_triangles, std::string t_path);

        inline unsigned int setTextureBuffer(std::vector<float> const& t_vertices, std::vector<unsigned int> const& t_indecies, std::string& t_path, unsigned int t_stride)
            { return setTextureBuffer(std::vector<float>(t_vertices), std::vector<unsigned int>(t_indecies), t_path, t_stride); }
        inline void setColour(glm::vec4 const& t_colour)
            { setColour(glm::vec4(t_colour)); }
        inline unsigned int setTexture(std::vector<Triangle2D> const& t_triangles, std::string& t_path)
            { return setTexture(std::vector<Triangle2D>(t_triangles), t_path); }

        unsigned int addTexture(std::string const& t_path);

        inline void setTextureId(unsigned int t_id)
            { m_currentTextureId = t_id; }   

        inline std::shared_ptr<Shader> shader()
            { return m_shader; }
        inline std::vector<unsigned int>& indecies()
            { return m_indecies; }
        inline OpenGL::VertexBuffer& buffer()
            {return *m_vertexBuffer; }
        inline OpenGL::VertexBufferLayout& layout()
            { return *m_layout; }
        inline unsigned int vertexSize() const
            { return m_stride; } 
        inline bool isTexture() const
            { return m_shader->usesTexture(); }
        inline bool isColour()
            { return !m_shader->usesTexture(); }   

        void bind();
        void unbind();

    private:
        void clear();
        void insertVertex(std::vector<float>&& t_vertex, bool t_useIndecies);
        void insertTriangles(std::vector<Triangle2D>&& t_trinagles, bool t_useIndecies);
        int findVertex(std::vector<float>& t_vertex);

        unsigned int m_stride = 0;
        bool m_bound = false;
        unsigned int m_currentTextureId = 1;
        unsigned int m_highestTextureId = 1;

        std::vector<float> m_vertices;
        std::vector<unsigned int> m_indecies;

        std::map<unsigned int, OpenGL::Texture> m_textures;
        std::unique_ptr<OpenGL::VertexBuffer> m_vertexBuffer;
        std::unique_ptr<OpenGL::VertexBufferLayout> m_layout;

        std::shared_ptr<Shader> m_shader;
    };
}