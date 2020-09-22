#pragma once
#include "triangle.hpp"
#include <array>
#include <iostream>

namespace MyEngine
{
    // Represents a triangle in 2D object.
    class Triangle2D : public Triangle
    {
    public:
        Triangle2D() { };
        Triangle2D(float t_ax, float t_bx, float t_cx,
                   float t_ay, float t_by, float t_cy);
        ~Triangle2D() { };

        // Adds a parameter with texture coordinates.
        void mapTexture(float t_tex_ax, float t_tex_bx, float t_tex_cx,
                        float t_tex_ay, float t_tex_by, float t_tex_cy) override;

        // Adds provided parameters at the end of vertecies.
        bool addParam(std::vector<float> const& params_a, 
                      std::vector<float> const& params_b, 
                      std::vector<float> const& params_c) override;
    };
}