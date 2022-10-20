#pragma once

#include "Renderer/material.hpp"
#include "Renderer/mesh2D.hpp"
#include "Renderer/drawable2D.hpp"
#include "Physics/body2D.hpp"
#include "Physics/physicsManager.hpp"

#include <memory>
#include <vector>

class Ball: public MyEngine::Renderer::Drawable2D, public MyEngine::Physics::Body2D
{
public:
    Ball(std::shared_ptr<MyEngine::Renderer::Material> t_material, 
             std::shared_ptr<MyEngine::Renderer::Mesh2D> t_mesh) : 
        Drawable2D(t_material, t_mesh), Body2D(t_mesh->vertices(), true) { }

    static std::shared_ptr<Ball> makeBall(std::shared_ptr<MyEngine::Renderer::Material>& t_material,
                                          std::shared_ptr<MyEngine::Renderer::Mesh2D>& t_mesh,
                                          std::shared_ptr<MyEngine::Renderer::Shader> t_shader,
                                          MyEngine::Physics::PhysicsManager& t_physics,
                                          unsigned int t_x, unsigned int t_y,unsigned int t_side);
};
