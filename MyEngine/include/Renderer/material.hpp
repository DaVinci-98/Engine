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
namespace MyEngine::Renderer
{
    class Material
    {
    public:
        Material(std::shared_ptr<Shader>& t_shader):
            m_shader(t_shader) { }

        void setColourBuffer(std::vector<float> && t_vertices, unsigned int t_stride);
        void setTextureBuffer(std::vector<float> && t_vertices, std::vector<unsigned int> && t_indecies, std::string& t_path, unsigned int t_stride);
        void setColour(std::vector<Triangle2D> && t_triangles);
        void setTexture(std::vector<Triangle2D> && t_triangles, std::string& t_path);

        inline void setTextureBuffer(std::vector<float> const& t_vertices, std::vector<unsigned int> const& t_indecies, std::string& t_path, unsigned int t_stride)
            { setTextureBuffer(std::vector<float>(t_vertices), std::vector<unsigned int>(t_indecies), t_path, t_stride); }
        inline void setColourBuffer(std::vector<float> const& t_vertices, unsigned int t_stride)
            { setColourBuffer(std::vector<float>(t_vertices), t_stride); }
        inline void setColour(std::vector<Triangle2D> const& t_triangles)
            { setColour(std::vector<Triangle2D>(t_triangles)); }
        inline void setTexture(std::vector<Triangle2D> const& t_triangles, std::string& t_path)
            { setTexture(std::vector<Triangle2D>(t_triangles), t_path); }

        inline std::shared_ptr<Shader>& shader()
            { return m_shader; }
        inline std::vector<unsigned int>& indecies()
            { return m_indecies; }
        inline OpenGL::VertexBuffer& buffer()
            {return *m_vertexBuffer; }
        inline OpenGL::VertexBufferLayout& layout()
            { return m_shader->layout(); }
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

        std::vector<float> m_vertices;
        std::vector<unsigned int> m_indecies;

        std::unique_ptr<OpenGL::Texture> m_texture;
        std::unique_ptr<OpenGL::VertexBuffer> m_vertexBuffer;

        std::shared_ptr<Shader> m_shader;
    };
}