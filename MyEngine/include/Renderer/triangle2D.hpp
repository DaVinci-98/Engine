#pragma once

#include "Renderer/triangle.hpp"

#include <array>
#include <iostream>

namespace MyEngine::Renderer
{
    // Represents a triangle in 2D object.
    class Triangle2D : public Triangle
    {
    public:
        Triangle2D() { };
        Triangle2D(float t_ax, float t_bx, float t_cx,
                   float t_ay, float t_by, float t_cy);

        // Adds provided parameters at the end of vertices.
        bool addParam(std::vector<float> const& params_a, 
                      std::vector<float> const& params_b, 
                      std::vector<float> const& params_c) override;
    };
}