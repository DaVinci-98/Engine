#include "Renderer/drawable2D.hpp"
#include "Renderer/shader.hpp"

#include <glm/ext/matrix_transform.hpp>

namespace MyEngine::Renderer
{
    void Drawable2D::setMaterial(std::shared_ptr<Material>& t_material)
    {
        if(m_mesh)
        {
            if(t_material -> isTexture() && m_mesh->indecies() != t_material->indecies()) return;
            if(m_material)
            {
                m_vertexArray -> unbind();
                m_vertexArray.reset();
            }
            m_material = t_material;
            makeArray();
        }
        else
            m_material = t_material;
    }

    void Drawable2D::setMesh(std::shared_ptr<Mesh2D>& t_mesh)
    {
        if(m_material)
        {
            if(m_material -> isTexture() && m_material->indecies() != t_mesh->indecies()) return;
            if(m_mesh)
            {
                m_vertexArray -> unbind();
                m_vertexArray.reset();
            }
            m_mesh = t_mesh;
            makeArray();
        }
        else
            m_mesh = t_mesh;
    }

    void Drawable2D::makeArray()
    {
        m_vertexArray = std::make_unique<OpenGL::VertexArray>();

        m_material -> buffer().bind();
        m_vertexArray -> addBuffer(m_material -> buffer(), 0, m_material->vertexSize(), m_material->layout());
        m_material -> buffer().unbind();

        m_mesh -> buffer().bind();
        m_vertexArray -> addBuffer(m_mesh -> buffer(), m_material->vertexSize(), m_mesh->vertexSize(), m_material->layout());
        m_mesh -> buffer().unbind();
    }

    void Drawable2D::bind()
    {
        if(m_bound) return;
        m_bound = true;

        m_mesh -> bind();
        m_material -> bind();
        m_vertexArray -> bind();

        m_material -> shader() -> setMat4Uniform(Shader::MODEL_UNIFORM, m_model);
    }

    void Drawable2D::unbind()
    {
        if(!m_bound) return;
        m_bound = false;

        m_mesh -> unbind();
        m_material -> unbind();
        m_vertexArray -> unbind();    
    }
}