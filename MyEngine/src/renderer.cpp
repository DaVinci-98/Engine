#include "glad/glad.h"

#include "renderer.hpp"
#include "glException.hpp"
#include "object.hpp"

namespace MyEngine
{
    void Renderer::clear() const
    {
        GL_CALL(glClear(GL_COLOR_BUFFER_BIT));
    }

    void Renderer::draw(Object& t_object, glm::mat4& t_MVP)
    {
        t_object.shader().bind();
        if(t_object.isTextured())
        { 
            t_object.texture().bind();
            t_object.shader().setUniform("u_texture", 0);
        }
        t_object.shader().setUniform("u_MVP", t_MVP);

        t_object.vertexArray().bind();
        t_object.indexBuffer().bind();

        GL_CALL(glDrawElements(GL_TRIANGLES, t_object.indexBuffer().count(), GL_UNSIGNED_INT, nullptr));
    }
}