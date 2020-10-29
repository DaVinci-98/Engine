#pragma once

#include "Renderer/material.hpp"
#include "Renderer/mesh2D.hpp"
#include "Renderer/drawable2D.hpp"
#include "Application/application.hpp"
#include "Physics/body2D.hpp"

#include <memory>
#include <vector>

class BreakableBlock: public MyEngine::Renderer::Drawable2D, public MyEngine::Physics::Body2D
{
public:
    struct BreakableBlockArgs
    {
        unsigned int m_x;
        unsigned int m_y;
        unsigned int m_width;
        unsigned int m_height;

        std::shared_ptr<MyEngine::Renderer::Material> m_material;
        std::shared_ptr<MyEngine::Renderer::Mesh2D> m_mesh;

        MyEngine::Renderer::Renderer& m_renderer;
        MyEngine::Physics::PhysicsManager& m_physics;
    };

    BreakableBlock(std::shared_ptr<MyEngine::Renderer::Material> t_material, 
             std::shared_ptr<MyEngine::Renderer::Mesh2D> t_mesh) : 
        Drawable2D(t_material, t_mesh), Body2D(t_mesh->vertices(), false) { }

    static std::shared_ptr<BreakableBlock> makeBreakableBlock(BreakableBlock::BreakableBlockArgs& t_args);

    inline void takeDamage()
        { --m_health; setHealthColour(); }
    
    inline glm::vec4& colour()
        { return m_colour; }
    
    inline unsigned int health() const
        { return m_health; }
        
    auto getRenderCallback()
        { return [this]() { this->material()->setColour(this->m_colour);}; }
        
private:
    void setHealthColour();
    unsigned int m_health = 5;
    glm::vec4 m_colour = glm::vec4(1, 1, 1, 1);
};