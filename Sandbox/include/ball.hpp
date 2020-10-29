#pragma once

#include "Renderer/material.hpp"
#include "Renderer/mesh2D.hpp"
#include "Renderer/drawable2D.hpp"
#include "Application/application.hpp"
#include "Physics/body2D.hpp"

#include <memory>
#include <vector>

class Ball: public MyEngine::Renderer::Drawable2D, public MyEngine::Physics::Body2D
{
public:
    struct BallArgs
    {
        unsigned int m_x;
        unsigned int m_y;
        unsigned int m_side;

        std::shared_ptr<MyEngine::Renderer::Material> m_material;
        std::shared_ptr<MyEngine::Renderer::Mesh2D> m_mesh;

        MyEngine::Renderer::Renderer& m_renderer;
        MyEngine::Glfw::Events::KeyEventListener& m_keyListener;
        MyEngine::Physics::PhysicsManager& m_physics;
    };

    Ball(std::shared_ptr<MyEngine::Renderer::Material> t_material, 
             std::shared_ptr<MyEngine::Renderer::Mesh2D> t_mesh) : 
        Drawable2D(t_material, t_mesh), Body2D(t_mesh->vertices(), true) { }

    static std::shared_ptr<Ball> makeBall(Ball::BallArgs& t_args);
        
    bool draw(MyEngine::Renderer::Renderer& t_renderer);
};