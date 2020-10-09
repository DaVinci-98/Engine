#include "glad/glad.h"

#include "openGL/renderer.hpp"
#include "openGL/glException.hpp"
#include "drawables/object.hpp"

namespace MyEngine
{
    bool Renderer::clear() const
    {
        try
        {
            GL_CALL(glClear(GL_COLOR_BUFFER_BIT));
            return true;
        }
        catch(GlException& e)
        {
            e.printErrors();
            return false;
        }
    }

    bool Renderer::draw(Object& t_object, glm::mat4& t_MVP)
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

        try
        {
            GL_CALL(glDrawElements(GL_TRIANGLES, t_object.indexBuffer().count(), GL_UNSIGNED_INT, nullptr));
            return true;
        }
        catch(GlException& e)
        {
            e.printErrors();
            return false;
        }
    }
}