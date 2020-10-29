#pragma once

#include <vector>
#include <array>
#include <iostream>

namespace MyEngine::Renderer
{
    // Base class for a triangle.
    class Triangle
    {
    public:
        Triangle() { }
        virtual ~Triangle() { }
        
        std::vector<float> const& vertecies() const { return m_vertecies; }
        std::vector<unsigned int> const& layout() const { return m_layout; }
 
        // Adds provided parameters at the end of vertecies.
        virtual bool addParam(std::vector<float> const& t_params_a, 
                              std::vector<float> const& t_params_b, 
                              std::vector<float> const& t_params_c) = 0;

        // Adds a parameter with texture coordinates.
        virtual void mapTexture(float t_tex_ax, float t_tex_bx, float t_tex_cx,
                                float t_tex_ay, float t_tex_by, float t_tex_cy) = 0;
    protected:
        bool m_textured = false;
        std::vector<float> m_vertecies;
        std::vector<unsigned int> m_layout;
    };
}