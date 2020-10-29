#include "ball.hpp"
#include "Glfw/Events/keyEvent.hpp"
#include "Glfw/Events/keyEventListener.hpp"

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

    void makeMaterial(std::shared_ptr<MyEngine::Renderer::Material>& t_material, MyEngine::Renderer::Renderer& t_renderer)
    {
        if(!t_material)
        {
            auto shader = t_renderer.shader(t_renderer.textureShader());
            t_material = std::make_shared<MyEngine::Renderer::Material>(shader);
            MyEngine::Renderer::Triangle2D bottomLeft(0, 0, 1, 1, 0, 0);
            MyEngine::Renderer::Triangle2D topRight(  1, 1, 0, 0, 1, 1);
            t_material -> setTexture(std::vector{ bottomLeft, topRight }, "/home/DaVinci/Projects/Engine/Sandbox/res/textures/ball.png");
        }
    }
}

std::shared_ptr<Ball> Ball::makeBall(Ball::BallArgs& t_args)
{
    makeMesh(t_args.m_mesh, t_args.m_side, t_args.m_side);
    makeMaterial(t_args.m_material, t_args.m_renderer);

    auto ball = std::make_shared<Ball>(t_args.m_material, t_args.m_mesh);

    ball -> setAssociatedModel(ball -> modelMatrix());
    ball -> applyTranslation(glm::vec2(t_args.m_x, t_args.m_y));

    std::string group = "ball";
    t_args.m_physics.registerPhysicsGroup(group, false);
    t_args.m_physics.addBody(group, ball);
    t_args.m_physics.getGroup(group).ambientAcceleration() = glm::vec2(0, -400.0f);
    return ball;
}
