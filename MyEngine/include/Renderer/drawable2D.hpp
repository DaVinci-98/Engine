#pragma once

#include "Renderer/material.hpp"
#include "Renderer/mesh2D.hpp"

#include "OpenGL/vertexArray.hpp"

#include <memory>
#include <vector>
#include <glm/gtc/matrix_transform.hpp>

namespace MyEngine::Renderer
{
    class Drawable2D
    {
    public:
        Drawable2D() { }
        Drawable2D(std::shared_ptr<Material>& t_material, std::shared_ptr<Mesh2D>& t_mesh)
            { setMaterial(t_material); 
              setMesh(t_mesh); }
        void setMaterial(std::shared_ptr<Material>& t_material);
        void setMesh(std::shared_ptr<Mesh2D>& t_mesh);

        inline void translate(glm::vec2& t_vec)
            { m_model = glm::translate(m_model, glm::vec3(t_vec, 0)); }
        inline void scale(float t_x, float t_y)
            { m_model = glm::scale(m_model, glm::vec3(t_x, t_y, 1)); }
        inline unsigned int vertexCount() const
            { return m_mesh -> vertexCount(); }
        inline glm::mat4& modelMatrix()
            { return m_model; }
        
        void bind();
        void unbind();
    private:
        void makeArray();

        glm::mat4 m_model = glm::mat4(1);
        bool m_bound = false;

        std::unique_ptr<OpenGL::VertexArray> m_vertexArray;
        std::shared_ptr<Material> m_material;
        std::shared_ptr<Mesh2D> m_mesh;
    };
}