#include "Renderer/drawable2D.hpp"
#include "Renderer/shader.hpp"

#include <glm/ext/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>

namespace MyEngine::Renderer
{
    void Drawable2D::setMaterial(std::shared_ptr<Material> t_material)
    {
        if(m_mesh)
        {
            if(t_material -> isTexture() && m_mesh->indecies() != t_material->indecies()) return;
            if(m_material)
            {
                m_vertexArray -> unbind();
                m_vertexArray.reset();
            }
        }
        m_material = t_material;
        makeArray();
    }

    void Drawable2D::setMesh(std::shared_ptr<Mesh2D> t_mesh)
    {
        if(m_material)
        {
            if(m_material -> isTexture() && m_material->indecies() != t_mesh->indecies()) return;
            if(m_mesh)
            {
                m_vertexArray -> unbind();
                m_vertexArray.reset();
            }
        }
        m_mesh = t_mesh;
        makeArray();
    }

    void Drawable2D::makeArray()
    {
        if(!m_material || !m_mesh) return;
        m_vertexArray = std::make_unique<OpenGL::VertexArray>();

        unsigned int offset = m_vertexArray -> setBuffer(m_mesh -> buffer(), m_mesh->layout());
        if(m_material -> isTexture()) m_vertexArray -> setBuffer(m_material -> buffer(), m_material->layout(), offset);
    }

    void Drawable2D::bind()
    {
        m_material -> bind();
        m_material -> shader() -> setMat4Uniform(Shader::MODEL_UNIFORM, *m_model, true);

        m_mesh -> unbind();
        m_vertexArray -> bind();
        m_mesh -> bind();
    }

    void Drawable2D::unbind()
    {
        m_mesh -> unbind();
        m_material -> unbind();
        m_vertexArray -> unbind();    
    }
}