#pragma once

#include "drawables/triangle.hpp"
#include "drawables/triangle2D.hpp"
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
    // Base class for an arbitrary displayable object
    class Object
    {
    public:
        Object() { };

        // Copy a triangle to obejct's triangle list.
        bool pushTriangle(Triangle const& t_triangle);
        // Move a triangle to obejct's triangle list.
        bool pushTriangle(Triangle && t_triangle);
        // Add a texture to the obejct.
        bool mapTexture(std::vector<Triangle2D> const& t_coordinates, std::string const& t_path);
        
        // Change trinagles into vertex buffers used by openGL.
        bool toVAO();

        bool isTextured() const { return m_texture != nullptr; }
        OpenGL::VertexArray & vertexArray() const { return *m_vertexArray; }
        OpenGL::IndexBuffer & indexBuffer() const { return *m_indexBuffer; }
        OpenGL::Shader & shader() const { return *m_shader; }
        OpenGL::Texture & texture() const { return *m_texture; }

    protected:
        virtual void triangleToVAO(std::unique_ptr<Triangle> const& t_triangle) = 0;

        std::vector<std::unique_ptr<Triangle> > m_triangles;
        std::vector<unsigned int> m_indecies;
        std::vector<std::vector<float> > m_buffer;

        std::unique_ptr<OpenGL::Texture> m_texture;
        std::unique_ptr<OpenGL::Shader> m_shader;
        std::unique_ptr<OpenGL::VertexArray> m_vertexArray;
        std::unique_ptr<OpenGL::IndexBuffer> m_indexBuffer;

    private:

        std::vector<std::unique_ptr<OpenGL::VertexBuffer> > m_buffers;
    };
}