#pragma once

#include "Renderer/material.hpp"
#include "Renderer/mesh2D.hpp"
#include "Renderer/drawable2D.hpp"
#include "Physics/body2D.hpp"

#include <memory>
#include <vector>

class Platform: public MyEngine::Renderer::Drawable2D, public MyEngine::Physics::Body2D
{
public:
    Platform(std::shared_ptr<MyEngine::Renderer::Material> t_material, 
             std::shared_ptr<MyEngine::Renderer::Mesh2D> t_mesh): 
        Drawable2D(t_material, t_mesh), Body2D(t_mesh -> vertices(), true) { }

    static std::shared_ptr<Platform> makePlatform(std::shared_ptr<MyEngine::Renderer::Material>& t_material,
                                                  std::shared_ptr<MyEngine::Renderer::Mesh2D>& t_mesh,
                                                  std::shared_ptr<MyEngine::Renderer::Shader> t_shader,
                                                  unsigned int t_x, unsigned int t_y,
                                                  unsigned int t_width, unsigned int t_height);
    
    inline glm::vec4& colour() { return m_colour; }
    inline void updateColour() { material() -> setColour(this -> m_colour); }

private:    
    glm::vec4 m_colour = glm::vec4(1, 1, 1, 1);
};
