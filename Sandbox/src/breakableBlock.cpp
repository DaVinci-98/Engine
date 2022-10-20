#include "breakableBlock.hpp"
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
            t_material -> setColour(glm::vec4(0, 0, 0, 0));
        }
    }
}

std::shared_ptr<BreakableBlock> BreakableBlock::makeBreakableBlock(
    std::shared_ptr<MyEngine::Renderer::Material>& t_material,
    std::shared_ptr<MyEngine::Renderer::Mesh2D>& t_mesh,
    std::shared_ptr<MyEngine::Renderer::Shader> t_shader,
    MyEngine::Physics::PhysicsManager& t_physics,
    unsigned int t_x, unsigned int t_y,
    unsigned int t_width, unsigned int t_height)
{
    makeMesh(t_mesh, t_width, t_height);
    makeMaterial(t_material, t_shader);

    auto breakableBlock = std::make_shared<BreakableBlock>(t_material, t_mesh);

    breakableBlock -> setAssociatedModel(breakableBlock -> modelMatrix());
    breakableBlock -> applyTranslation(glm::vec2(t_x, t_y));


    std::string group = "breakableBlock";
    t_physics.registerPhysicsGroup(group, false);
    t_physics.addBody(group, breakableBlock);
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
