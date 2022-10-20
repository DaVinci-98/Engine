#include "breakableBlock.hpp"
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
            auto shader = t_renderer.shader(t_renderer.colourShader());
            t_material = std::make_shared<MyEngine::Renderer::Material>(shader);
            t_material->setColour(glm::vec4(0, 0, 0, 0));
        }
    }
}

std::shared_ptr<BreakableBlock> BreakableBlock::makeBreakableBlock(BreakableBlock::BreakableBlockArgs& t_args)
{
    makeMesh(t_args.m_mesh, t_args.m_width, t_args.m_height);
    makeMaterial(t_args.m_material, t_args.m_renderer);

    auto breakableBlock = std::make_shared<BreakableBlock>(t_args.m_material, t_args.m_mesh);

    breakableBlock -> setAssociatedModel(breakableBlock -> modelMatrix());
    breakableBlock -> applyTranslation(glm::vec2(t_args.m_x, t_args.m_y));


    std::string group = "breakableBlock";
    t_args.m_physics.registerPhysicsGroup(group, false);
    t_args.m_physics.addBody(group, breakableBlock);
    return breakableBlock;
}

void BreakableBlock::setHealthColour()
{
    switch (m_health)
    {
    case 4:
        m_colour = glm::vec4(0, 1, 0, 1);
        break;
    case 3:
        m_colour = glm::vec4(1, 1, 0, 1);
        break;
    case 2:
        m_colour = glm::vec4(1, 0.5, 0, 1);
        break;    
    case 1:
        m_colour = glm::vec4(1, 0, 0, 1);
        break;
    case 0:
        m_colour = glm::vec4(0, 0, 0, 1);
        break;
    default:
        break;
    }
}
