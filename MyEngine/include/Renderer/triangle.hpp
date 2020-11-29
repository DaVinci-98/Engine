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
        
        std::vector<float> const& vertices() const { return m_vertices; }
        std::vector<unsigned int> const& layout() const { return m_layout; }
 
        // Adds provided parameters at the end of vertices.
        virtual bool addParam(std::vector<float> const& t_params_a, 
                              std::vector<float> const& t_params_b, 
                              std::vector<float> const& t_params_c) = 0;

    protected:
        std::vector<float> m_vertices;
        std::vector<unsigned int> m_layout;
    };
}