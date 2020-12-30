#pragma once

#include "Renderer/triangle2D.hpp"
#include "OpenGL/vertexBuffer.hpp"
#include "OpenGL/vertexBufferLayout.hpp"
#include "OpenGL/indexBuffer.hpp"

#include <memory>

namespace MyEngine::Renderer
{
    class Mesh2D
    {
    public:
        void setBuffer(std::vector<float> && t_vertices, std::vector<unsigned int> && t_indecies, unsigned int t_stride);
        void setTriangles(std::vector<Triangle2D> && t_triangles);

        void setBuffer(std::vector<float> const& t_vertices, std::vector<unsigned int> const& t_indecies, unsigned int t_stride)
            { setBuffer(std::vector<float>(t_vertices), std::vector<unsigned int>(t_indecies), t_stride); }
        void setTriangles(std::vector<Triangle2D> const& t_triangles)
            { setTriangles(std::vector<Triangle2D>(t_triangles)); }

        inline std::vector<unsigned int>& indecies()
            { return m_indecies; }
        inline std::vector<float>& vertices()
            { return m_vertices; }
        inline OpenGL::VertexBuffer& buffer()
            {return *m_vertexBuffer;}
        inline unsigned int vertexSize() const
            { return m_stride; }
        inline unsigned int vertexCount() const
            { return m_indecies.size(); }    
        inline OpenGL::VertexBufferLayout& layout()
            { return *m_layout; }

        void bind();
        void unbind();

    private:
        void clear();
        void insertVertex(std::vector<float>&& t_vertex);
        void insertTriangles(std::vector<Triangle2D>&& t_trinagles);
        int findVertex(std::vector<float>& t_vertex);

        std::vector<float> m_vertices;
        std::vector<unsigned int> m_indecies;

        std::unique_ptr<OpenGL::VertexBuffer> m_vertexBuffer;
        std::unique_ptr<OpenGL::IndexBuffer> m_indexBuffer;
        std::unique_ptr<OpenGL::VertexBufferLayout> m_layout;

        unsigned int m_stride = 0;
        bool m_bound = false;
    };
}