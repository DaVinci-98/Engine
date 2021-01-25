#pragma once

#include "Renderer/material.hpp"
#include "Renderer/mesh2D.hpp"

#include "OpenGL/vertexArray.hpp"

#include <memory>
#include <vector>
#include <glm/gtc/matrix_transform.hpp>

namespace MyEngine::Renderer
{
    /**
     * @brief Combines Mesh2D and Material objects for easier rendering.
     * 
     */
    class Drawable2D
    {
    public:
        /**
         * @brief Construct a new Drawable2D object.
         * 
         */
        Drawable2D() { }
        /**
         * @brief Construct a new Drawable2D object.
         * 
         * @param t_material Material to render drawable with.
         * @param t_mesh Drawable's mesh.
         */
        Drawable2D(std::shared_ptr<Material> t_material, std::shared_ptr<Mesh2D> t_mesh)
            { setMaterial(t_material); 
              setMesh(t_mesh); }
        /**
         * @brief Set the Material for this drawable.
         * 
         * @param t_material shared pointer to a material object.
         */
        void setMaterial(std::shared_ptr<Material>& t_material);
        /**
         * @brief Set the Material for this drawable.
         * 
         * @param t_mesh shared pointer to a mesh object.
         */
        void setMesh(std::shared_ptr<Mesh2D>& t_mesh);

        /**
         * @brief Set the Mesh and Material for this drawable.
         * 
         * @param t_mesh shared pointer to a mesh object.
         * @param t_material shared pointer to a material object.
         */
        void setMeshMaterial(std::shared_ptr<Mesh2D>& t_mesh, std::shared_ptr<Material>& t_material);

        /**
         * @brief Translate the drawable by provided vector.
         * 
         */
        inline void translate(glm::vec2&& t_vec)
            { *m_model = glm::translate(*m_model, glm::vec3(t_vec, 0));
              m_modelChanged = true; }
        /**
         * @brief Translate the drawable by provided vector.
         * 
         */
        inline void translate(glm::vec2 const& t_vec)
            { *m_model = glm::translate(*m_model, glm::vec3(t_vec, 0));
              m_modelChanged = true; }
        /**
         * @brief Scale the drawable.
         * 
         * @param t_x scale to be applied in x axis.
         * @param t_y scale to be applied in y axis.
         */
        inline void scale(float t_x, float t_y)
            { *m_model = glm::scale(*m_model, glm::vec3(t_x, t_y, 1));
              m_modelChanged = true; }

        /**
         * @brief Returns a shared pointer to underlying Material.
         * 
         */
        inline std::shared_ptr<Material> material()
            { return m_material; }
       /**
         * @brief Returns a shared pointer to underlying Mesh2D.
         * 
         */
        inline std::shared_ptr<Mesh2D> mesh()
            { return m_mesh; }
       /**
         * @brief Returns a number of vertexes in Mesh2D.
         * 
         * @sa Mesh2D::vertexCount()
         * 
         */
        inline unsigned int vertexCount() const
            { return m_mesh -> vertexCount(); }
        /**
         * @brief Returns a model Matrix for this drawable.
         * 
         */
        inline std::shared_ptr<glm::mat4> modelMatrix()
            { return m_model; }
        
        /**
         * @brief Bind the underlying Mesh2D and Material.
         * 
         */
        void bind();
        /**
         * @brief Unbind the underlying Mesh2D and Material.
         * 
         */
        void unbind();
        
    private:
        void makeArray();

        std::shared_ptr<glm::mat4> m_model = std::make_shared<glm::mat4>(1);
        bool m_modelChanged = false;

        std::unique_ptr<OpenGL::VertexArray> m_vertexArray;
        std::shared_ptr<Material> m_material;
        std::shared_ptr<Mesh2D> m_mesh;
    };
}