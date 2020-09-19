#pragma once
#include "triangle.hpp"
#include "triangle2D.hpp"
#include "texture.hpp"
#include "vertexArray.hpp"
#include "indexBuffer.hpp"
#include "shader.hpp"
#include <vector>
#include <tuple>
#include <array>
#include <memory>

namespace MyEngine
{
    class Object
    {
    public:
        Object() { };

        bool pushTriangle(Triangle const& t_triangle);
        bool pushTriangle(Triangle && t_triangle);
        bool mapTexture(std::vector<Triangle2D> const& t_coordinates, std::string const& t_path);
        
        bool bake();

        bool isTextured() const { return m_texture != nullptr; }
        VertexArray & vertexArray() const { return *m_vertexArray; }
        IndexBuffer & indexBuffer() const { return *m_indexBuffer; }
        Shader & shader() const { return *m_shader; }
        Texture & texture() const { return *m_texture; }

    protected:
        virtual void bakeTriangle(std::unique_ptr<Triangle> const& t_triangle) = 0;

        std::vector<std::unique_ptr<Triangle> > m_triangles;
        std::vector<unsigned int> m_indecies;
        std::vector<std::vector<float> > m_buffer;

        std::unique_ptr<Texture> m_texture;
        std::unique_ptr<Shader> m_shader;
        std::unique_ptr<VertexArray> m_vertexArray;
        std::unique_ptr<IndexBuffer> m_indexBuffer;

    private:

        std::vector<std::unique_ptr<VertexBuffer> > m_buffers;
    };
}