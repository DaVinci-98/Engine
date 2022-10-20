#pragma once

#include "Renderer/material.hpp"
#include "Renderer/mesh2D.hpp"
#include "Renderer/drawable2D.hpp"
#include "Application/application.hpp"
#include "Physics/body2D.hpp"

#include <memory>
#include <vector>

class Platform: public MyEngine::Renderer::Drawable2D, public MyEngine::Physics::Body2D
{
public:
    struct PlatformArgs
    {
        unsigned int m_x;
        unsigned int m_y;
        unsigned int m_width;
        unsigned int m_height;

        std::shared_ptr<MyEngine::Renderer::Material> m_material;
        std::shared_ptr<MyEngine::Renderer::Mesh2D> m_mesh;

        MyEngine::Renderer::Renderer& m_renderer;
        MyEngine::Glfw::Events::KeyEventListener& m_keyListener;
        MyEngine::Physics::PhysicsManager& m_physics;
    };

    Platform(std::shared_ptr<MyEngine::Renderer::Material> t_material, 
             std::shared_ptr<MyEngine::Renderer::Mesh2D> t_mesh) : 
        Drawable2D(t_material, t_mesh), Body2D(t_mesh->vertices(), true) { }

    static std::shared_ptr<Platform> makePlatform(Platform::PlatformArgs& t_args);
    
    glm::vec4& colour()
        { return m_colour; }
        
    auto getRenderCallback()
        { return [this]() { this->material()->setColour(this->m_colour);}; }

private:    
    glm::vec4 m_colour = glm::vec4(1, 1, 1, 1);
};