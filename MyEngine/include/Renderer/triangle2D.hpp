#pragma once

#include "Renderer/triangle.hpp"

#include <array>
#include <iostream>

namespace MyEngine::Renderer
{
    /**
     * @brief Represents a triangle in 2D mesh, inherits from Triangle class.
     * 
     */
    class Triangle2D : public Triangle
    {
    public:
        /**
         * @brief Construct a new Triangle2D object.
         * 
         */
        Triangle2D() { };
        /**
         * @brief Construct a new Triangle2D bject with predefined coordinates.
         * 
         */
        Triangle2D(float t_ax, float t_bx, float t_cx,
                   float t_ay, float t_by, float t_cy);

        /**
         * @brief Adds provided parameters at the end of vertices.
         * 
         * @param t_params_a vector of floats to be added to first  vertex
         * @param t_params_b vector of floats to be added to second vertex
         * @param t_params_c vector of floats to be added to third  vertex
         * @return true if the parameter was succesfully added.
         */
        bool addParam(std::vector<float> const& params_a, 
                      std::vector<float> const& params_b, 
                      std::vector<float> const& params_c) override;
    };
}