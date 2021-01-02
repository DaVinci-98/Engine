#pragma once

#include "Renderer/triangle2D.hpp"
#include "OpenGL/vertexBuffer.hpp"
#include "OpenGL/vertexBufferLayout.hpp"
#include "OpenGL/indexBuffer.hpp"

#include <memory>

namespace MyEngine::Renderer
{
    /**
     * @brief Object representing a 2D mesh.
     * 
     */
    class Mesh2D
    {
    public:
        /**
         * @brief Set a buffer of vertices used in this mesh
         * with their indexes.
         * 
         * @param t_vertices vertices squashed into vector of floats.
         * @param t_indecies indexes of vertices
         * @param t_stride number of floats in buffer used by one vertex
         * 
         * @example mesh is drawn using indexes of vertices. 
         * Index buffer [0,1,2,2,3,0] creates a mesh with 4 vertices and 2 traingles.
         * First triangle is drawn by vertices on indexes 0,1,2 in buffer,
         * the second one by vertices on indexes 2,3,0 in buffer. 
         * 
         */
        void setBuffer(std::vector<float> && t_vertices, std::vector<unsigned int> && t_indecies, unsigned int t_stride);
        /**
         * @brief Set Triangle2D objects used in buffer.
         * 
         */
        void setTriangles(std::vector<Triangle2D> && t_triangles);

        /**
         * @brief Set a buffer of vertices used in this mesh
         * with their indexes.
         * 
         * @param t_vertices vertices squashed into vector of floats.
         * @param t_indecies indexes of vertices
         * @param t_stride number of floats in buffer used by one vertex
         * 
         * @example mesh is drawn using indexes of vertices. 
         * Index buffer [0,1,2,2,3,0] creates a mesh with 4 vertices and 2 traingles.
         * First triangle is drawn by vertices on indexes 0,1,2 in buffer,
         * the second one by vertices on indexes 2,3,0 in buffer. 
         * 
         */
        inline void setBuffer(std::vector<float> const& t_vertices, std::vector<unsigned int> const& t_indecies, unsigned int t_stride)
            { setBuffer(std::vector<float>(t_vertices), std::vector<unsigned int>(t_indecies), t_stride); }
        /**
         * @brief Set Triangle2D objects used in buffer.
         * 
         */
        inline void setTriangles(std::vector<Triangle2D> const& t_triangles)
            { setTriangles(std::vector<Triangle2D>(t_triangles)); }

        /**
         * @brief Returns a reference to vector of indecies in this mesh. 
         * 
         */
        inline std::vector<unsigned int>& indecies()
            { return m_indecies; }
        /**
         * @brief Returns a reference to vector of vertices in this mesh. 
         * 
         */
        inline std::vector<float>& vertices()
            { return m_vertices; }
        /**
         * @brief Returns a reference to underlying OpenGL::VertexBuffer for this mesh.
         * 
         */
        inline OpenGL::VertexBuffer& buffer()
            {return *m_vertexBuffer;}
        /**
         * @brief Returns size of vertex (number of float values in it) in this mesh.
         * 
         */
        inline unsigned int vertexSize() const
            { return m_stride; }
        /**
         * @brief Returns number of vertices in this mesh.
         * (it's the number of vertices drawn. not the size of vertex buffer)
         * 
         */
        inline unsigned int vertexCount() const
            { return m_indecies.size(); }    
        /**
         * @brief Returns a reference to underlying OpenGL::VertexBufferLayout for this mesh.
         * 
         */
        inline OpenGL::VertexBufferLayout& layout()
            { return *m_layout; }

        /**
         * @brief Bind the underlying openGl buffers for this mesh.
         * 
         */
        void bind();
        /**
         * @brief Unbind the underlying openGl buffers for this mesh.
         * 
         */
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