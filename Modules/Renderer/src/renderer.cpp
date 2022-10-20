#include "glad/gl.h" 

#include "Renderer/renderer.hpp"
#include "OpenGL/glException.hpp"
#include "Logger/logger.hpp"

#include <glm/gtc/matrix_transform.hpp>

namespace MyEngine::Renderer
{
    bool Renderer::initialize()
    {
        GL_CALL(glEnable(GL_BLEND));
        GL_CALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        Logger::Logger::log<Renderer>() -> info(
            "[Init]: Done"); 

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
        if(m_lastMaterial != t_drawable.material())
        {
            if(m_lastMaterial)
                m_lastMaterial -> unbind();
            m_lastMaterial = t_drawable.material();
            m_lastMaterial -> bind();
        }

        t_drawable.bind();
        bool drawn = draw(t_drawable.vertexCount());
        if(!drawn)
            m_lastMaterial -> unbind();

        return drawn;
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