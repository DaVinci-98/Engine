#pragma once

#include "vertexArray.hpp"
#include "indexBuffer.hpp"
#include "shader.hpp"
#include "object.hpp"
#include <memory>

namespace MyEngine
{
    class Renderer
    {
    public:
        Renderer() { };
        ~Renderer() { };
        void clear() const;
        void draw(Object& t_object, glm::mat4& t_MVP);
        void draw(VertexArray& t_va, IndexBuffer& t_ib, Shader& t_sh, GLenum t_mode);
    };
}