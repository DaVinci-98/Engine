#include "ball.hpp"
#include "Glfw/Events/keyEvent.hpp"

#include <iostream>

namespace
{
    void makeMesh(std::shared_ptr<MyEngine::Renderer::Mesh2D>& t_mesh, unsigned int t_width, unsigned int t_height)
    {
        if(!t_mesh)
        {
            MyEngine::Renderer::Triangle2D bottomLeft(0, 0, t_width, t_height, 0, 0);
            MyEngine::Renderer::Triangle2D topRight(t_width, t_width, 0, 0, t_height, t_height);

            t_mesh = std::make_shared<MyEngine::Renderer::Mesh2D>();
            t_mesh -> setTriangles(std::vector{ bottomLeft, topRight });
        }
    }

    void makeMaterial(std::shared_ptr<MyEngine::Renderer::Material>& t_material, 
                      std::shared_ptr<MyEngine::Renderer::Shader> t_shader)
    {
        if(!t_material)
        {
            t_material = std::make_shared<MyEngine::Renderer::Material>(t_shader);
            MyEngine::Renderer::Triangle2D bottomLeft(0, 0, 1, 1, 0, 0);
            MyEngine::Renderer::Triangle2D topRight(  1, 1, 0, 0, 1, 1);
            t_material -> setTexture(std::vector{ bottomLeft, topRight }, "/home/davinci/Projects/Engine/Sandbox/res/textures/ball.png");
        }
    }
}

std::shared_ptr<Ball> Ball::makeBall(std::shared_ptr<MyEngine::Renderer::Material>& t_material,
                                     std::shared_ptr<MyEngine::Renderer::Mesh2D>& t_mesh,
                                     std::shared_ptr<MyEngine::Renderer::Shader> t_shader,
                                     MyEngine::Physics::PhysicsManager& t_physics,
                                     unsigned int t_x, unsigned int t_y, unsigned int t_side)
{
    makeMesh(t_mesh, t_side, t_side);
    makeMaterial(t_material, t_shader);

    auto ball = std::make_shared<Ball>(t_material, t_mesh);

    ball -> setAssociatedModel(ball -> modelMatrix());
    ball -> applyTranslation(glm::vec2(t_x, t_y));

    std::string group = "ball";
    t_physics.registerPhysicsGroup(group, false);
    t_physics.addBody(group, ball);
    t_physics.getGroup(group).ambientAcceleration() = glm::vec2(0, -400.0f);
    return ball;
}
