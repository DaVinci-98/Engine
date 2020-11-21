#include "glad/glad.h"

#include "Renderer/renderer.hpp"
#include "Renderer/object.hpp"
#include "OpenGL/glException.hpp"
#include <glm/gtc/matrix_transform.hpp>

namespace MyEngine::Renderer
{
    bool Renderer::clear() const
    {
        try
        {
            GL_CALL(glClear(GL_COLOR_BUFFER_BIT));
            return true;
        }
        catch(OpenGL::GlException& e)
        {
            e.printErrors();
            return false;
        }
    }

    void Renderer::resizeWindow(int t_width, int t_height)
    { 
        glViewport(0, 0, t_width, t_height); 
        setOrtho2D(t_width, t_height);
    }

    void Renderer::setOrtho2D(int t_width, int t_height)
    {
        m_projection = glm::ortho<float>(0.0f, (float) t_width, 0.0f, (float) t_height, -1.0f, 1.0f);
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
        catch(OpenGL::GlException& e)
        {
            e.printErrors();
            return false;
        }
    }
}