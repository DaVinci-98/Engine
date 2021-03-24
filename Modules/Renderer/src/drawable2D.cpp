#include "Renderer/drawable2D.hpp"
#include "Renderer/shader.hpp"
#include "Helpers/logger.hpp"

#include <glm/ext/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

namespace MyEngine::Renderer
{
    void Drawable2D::setMeshMaterial(std::shared_ptr<Mesh2D>& t_mesh, std::shared_ptr<Material>& t_material)
    {
        if(t_material -> isTexture() && t_mesh->indicies().size() != t_material->indicies().size())
        {
            Helpers::Logger::log<Drawable2D>(Helpers::Logger::LogType::ERROR,
                "[setMaterial()]: number of indicies in mesh and material does not match.");
            return;
        }

        if(m_mesh && m_material)
        {
            m_vertexArray -> unbind();
            m_vertexArray.reset();
        }

        m_material = t_material;
        m_mesh = t_mesh;
        makeArray();
    }

    void Drawable2D::setMaterial(std::shared_ptr<Material>& t_material)
    {
        if(m_mesh)
        {
            if(t_material -> isTexture() && m_mesh->indicies().size() != t_material->indicies().size())
            {
                Helpers::Logger::log<Drawable2D>(Helpers::Logger::LogType::ERROR,
                    "[setMaterial()]: number of indicies in mesh and material does not match.");
                return;
            }
            if(m_material)
            {
                m_vertexArray -> unbind();
                m_vertexArray.reset();
            }
        }
        m_material = t_material;

        if(m_material && m_mesh) makeArray();
    }

    void Drawable2D::setMesh(std::shared_ptr<Mesh2D>& t_mesh)
    {
        if(m_material)
        {
            if(m_material -> isTexture() && t_mesh->indicies().size() != m_material->indicies().size())
            {
                Helpers::Logger::log<Drawable2D>(Helpers::Logger::LogType::ERROR,
                    "[setMaterial()]: number of indicies in mesh and material does not match.");
                return;
            }
            if(m_mesh)
            {
                m_vertexArray -> unbind();
                m_vertexArray.reset();
            }
        }
        m_mesh = t_mesh;
        if(m_material && m_mesh) makeArray();
    }

    void Drawable2D::makeArray()
    {
        if(!m_material || !m_mesh)
        {
            Helpers::Logger::log<Drawable2D>(Helpers::Logger::LogType::ERROR,
                "[makeArray()]: Drawable has to have both Material and Mesh2D set in order to create a VAO");
            return;
        }
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