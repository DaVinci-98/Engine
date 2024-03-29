#include "Renderer/mesh2D.hpp"

#include <algorithm>

namespace MyEngine::Renderer
{
    void Mesh2D::setBuffer(std::vector<float> && t_vertices, std::vector<unsigned int> && t_indicies, unsigned int t_stride)
    {
        if(m_stride != 0) clear();
        m_stride = t_stride;

        m_vertices = std::move(t_vertices);
        m_indicies = std::move(t_indicies);

        m_indexBuffer = std::make_unique<OpenGL::IndexBuffer>(m_indicies);
        m_vertexBuffer = std::make_unique<OpenGL::VertexBuffer>(m_vertices);
        m_layout = std::make_unique<OpenGL::VertexBufferLayout>();

        m_layout -> push<float>(m_stride);
    }

    void Mesh2D::setTriangles(std::vector<Triangle2D> && t_triangles, bool t_colapse)
    {
        if(m_stride != 0) clear();

        insertTriangles(std::move(t_triangles), t_colapse);

        m_indexBuffer = std::make_unique<OpenGL::IndexBuffer>(m_indicies);
        m_vertexBuffer = std::make_unique<OpenGL::VertexBuffer>(m_vertices);
        m_layout = std::make_unique<OpenGL::VertexBufferLayout>();

        m_layout -> push<float>(m_stride);
    }

    void Mesh2D::insertTriangles(std::vector<Triangle2D>&& t_triangles, bool t_colapse)
    {
        m_stride = static_cast<unsigned int>(t_triangles[0].vertices().size() / 3);

        for(auto& triangle : t_triangles)
        {
            insertVertex(std::vector<float>(triangle.vertices().begin(),              triangle.vertices().begin() +   m_stride), t_colapse);
            insertVertex(std::vector<float>(triangle.vertices().begin() +   m_stride, triangle.vertices().begin() + 2*m_stride), t_colapse);
            insertVertex(std::vector<float>(triangle.vertices().begin() + 2*m_stride, triangle.vertices().begin() + 3*m_stride), t_colapse);
        }
    }

    void Mesh2D::insertVertex(std::vector<float>&& t_vertex, bool t_colapse)
    {
        int index = -1;
        if(t_colapse)
            index = findVertex(t_vertex);
        if(index < 0)
        {
            m_vertices.insert(m_vertices.end(),
                std::make_move_iterator(t_vertex.begin()),
                std::make_move_iterator(t_vertex.end()));
            unsigned int new_index = static_cast<unsigned int>(m_vertices.size() / m_stride) - 1;
            m_indicies.push_back(new_index);
        }
        else
            m_indicies.push_back(index);
    }

    int Mesh2D::findVertex(std::vector<float>& t_vertex)
    {
        auto begin = m_vertices.begin();
        while(begin < m_vertices.end())
        {
            begin = std::search(begin, m_vertices.end(), t_vertex.begin(), t_vertex.end());
            int dist = std::distance(m_vertices.begin(), begin);
            if(dist%m_stride == 0 && begin < m_vertices.end())
                return static_cast<int>(dist / m_stride);
            if(begin < m_vertices.end()) begin++;
        }
        return -1;
    }


    void Mesh2D::bind()
    {
        if(m_bound) return;
        m_bound = true;

        m_indexBuffer -> bind();
    }

    void Mesh2D::unbind()
    {
        if(!m_bound) return;
        m_bound = false;

        m_vertexBuffer -> unbind();
        m_indexBuffer -> unbind();
    }

    void Mesh2D::clear()
    {
        m_stride = 0;

        m_vertexBuffer -> unbind();
        m_indexBuffer -> unbind();

        m_vertexBuffer.reset();
        m_indexBuffer.reset();
        m_layout.reset();

        m_vertices.clear();
        m_indicies.clear();
    }
}