#include "glad/glad.h"

#include "Renderer/renderer.hpp"
#include "OpenGL/glException.hpp"
#include "Glfw/window.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

namespace MyEngine::Renderer
{
    bool Renderer::initialize()
    {
        if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) return false;
        GL_CALL(glEnable(GL_BLEND));
        GL_CALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        return true;
    }

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

    bool Renderer::draw(Drawable2D& t_drawable)
    {
        t_drawable.bind();
        return draw(t_drawable.vertexCount());
    }

    bool Renderer::draw(unsigned int t_count)
    {
        try
        {
            GL_CALL(glDrawElements(GL_TRIANGLES, t_count, GL_UNSIGNED_INT, nullptr));
            return true;
        }
        catch(OpenGL::GlException& e)
        {
            e.printErrors();
            return false;
        }
    }

    std::string Renderer::colourShader()
    {
        std::string name = "ColourShader";
        if(m_activeShaders.find(name) != m_activeShaders.end())
            return name;

        auto shader = Shader::createColourShader();
        shader -> setMat4Uniform(Shader::PROJECTION_UNIFORM, m_projection);
        shader -> setMat4Uniform(Shader::VIEW_UNIFORM, m_view);
        m_activeShaders.insert(std::make_pair(name, shader));

        return name;
    }

    std::string Renderer::textureShader()
    {
        std::string name = "TextureShader";
        if(m_activeShaders.find(name) != m_activeShaders.end())
            return name;
        auto shader = Shader::createTextureShader();
        shader -> setMat4Uniform(Shader::PROJECTION_UNIFORM, m_projection);
        shader -> setMat4Uniform(Shader::VIEW_UNIFORM, m_view);
        m_activeShaders.insert(std::make_pair(name, shader));

        return name;
    }
}