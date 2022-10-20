#pragma once

#include "Renderer/material.hpp"
#include "Renderer/mesh2D.hpp"
#include "Renderer/drawable2D.hpp"
#include "Physics/body2D.hpp"
#include "Physics/physicsManager.hpp"

#include <memory>
#include <vector>

class BreakableBlock: public MyEngine::Renderer::Drawable2D, public MyEngine::Physics::Body2D
{
public:
    BreakableBlock(std::shared_ptr<MyEngine::Renderer::Material> t_material, 
             std::shared_ptr<MyEngine::Renderer::Mesh2D> t_mesh) : 
        Drawable2D(t_material, t_mesh), Body2D(t_mesh->vertices(), false) { }

    static std::shared_ptr<BreakableBlock> makeBreakableBlock(
        std::shared_ptr<MyEngine::Renderer::Material>& t_material,
        std::shared_ptr<MyEngine::Renderer::Mesh2D>& t_mesh,
        std::shared_ptr<MyEngine::Renderer::Shader> t_shader,
        MyEngine::Physics::PhysicsManager& t_physics,
        unsigned int t_x, unsigned int t_y,
        unsigned int t_width, unsigned int t_height);

    inline void takeDamage() { --m_health; setHealthColour(); }
    inline glm::vec4& colour() { return m_colour; }
    inline unsigned int health() const { return m_health; }
    inline void updateColour() { material() -> setColour(this -> m_colour); }
        
private:
    void setHealthColour();
    unsigned int m_health = 5;
    glm::vec4 m_colour = glm::vec4(1, 1, 1, 1);
};