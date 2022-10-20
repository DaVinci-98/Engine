#include "platform.hpp"
#include "Glfw/Events/keyEvent.hpp"
#include "Renderer/shader.hpp"

#include <iostream>

namespace
{
    void makeMesh(std::shared_ptr<MyEngine::Renderer::Mesh2D>& t_mesh, 
                  unsigned int t_width, unsigned int t_height)
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

std::shared_ptr<Platform> Platform::makePlatform(std::shared_ptr<MyEngine::Renderer::Material>& t_material,
                                                 std::shared_ptr<MyEngine::Renderer::Mesh2D>& t_mesh,
                                                 std::shared_ptr<MyEngine::Renderer::Shader> t_shader,
                                                 unsigned int t_x, unsigned int t_y,
                                                 unsigned int t_width, unsigned int t_height)
{   
    makeMesh(t_mesh, t_width, t_height);
    makeMaterial(t_material, t_shader);

    auto platform = std::make_shared<Platform>(t_material, t_mesh);

    platform -> setAssociatedModel(platform -> modelMatrix());
    platform -> applyTranslation(glm::vec2(t_x, t_y));

    return platform;
    return nullptr;
}

