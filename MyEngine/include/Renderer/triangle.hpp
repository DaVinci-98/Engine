#pragma once

#include <vector>

namespace MyEngine::Renderer
{
    /**
     * @brief Base class for a triangle.
     * 
     */
    class Triangle
    {
    public:
        /**
         * @brief Construct a new Triangle object.
         * 
         */
        Triangle() { }
        /**
         * @brief Destroy the Triangle object.
         * 
         */
        virtual ~Triangle() { }
        
        /**
         * @brief Get const reference to the vertices of this trinagle squashed into on vector of floats 
         * 
         */
        std::vector<float> const& vertices() const 
            { return m_vertices; }
        /**
         * @brief Get const reference to layout of the vertices in this triangle.
         * 
         * For example, layout [3,4] would mean that vertices consist of two vectors of floats, 
         * first with size 3, second with size 4.
         * 
         */
        std::vector<unsigned int> const& layout() const 
            { return m_layout; }
 
        /**
         * @brief Adds provided parameters at the end of vertices.
         * 
         * @param t_params_a vector of floats to be added to first  vertex
         * @param t_params_b vector of floats to be added to second vertex
         * @param t_params_c vector of floats to be added to third  vertex
         * @return true if the parameter was successfully added.
         */
        virtual bool addParam(std::vector<float> const& t_params_a, 
                              std::vector<float> const& t_params_b, 
                              std::vector<float> const& t_params_c) = 0;

    protected:
        std::vector<float> m_vertices;
        std::vector<unsigned int> m_layout;
    };
}