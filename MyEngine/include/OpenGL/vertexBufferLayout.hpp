#pragma once

#include <vector>
#include <iostream>

namespace MyEngine::OpenGL
{
    /**
     * @brief Layout of vertices in vertex buffer.
     * 
     */
    struct VertexBufferElement
    {
        unsigned int count;
        unsigned int type;
        unsigned int typeSize;
        unsigned int normalized;
    };

    /**
     * @brief Represents a layout of the vertex buffer.
     * 
     */
    class VertexBufferLayout
    {
    public:
        VertexBufferLayout() { };

        /**
         * @brief Add values to the layout.
         * 
         * @tparam T type of values added.
         * @param t_count Number of values added.
         * 
         */
        template<typename T> void push(size_t t_count);

        /**
         * @brief Length in bytes of one vertex.
         * 
         * @example [3 floats](for coordinates) returns 3 * sizeof(float)
         * 
         */
        unsigned int stride() const 
            { return m_stride; }
        /**
         * @brief Number of element in vertex's layout.
         * 
         * @example [3 floats](for coordinates)[4 floats](for colour) returns 2
         */
        unsigned int numElements() const 
            { return m_elements.size(); }
        /**
         * @brief Returns a refrence to layout element at given position.
         * 
         */
        VertexBufferElement const& elementAt(unsigned int t_pos) const 
            { return m_elements.at(t_pos); }
        /**
         * @brief Returns a reference to underlying vector.
         * 
         */
        std::vector<VertexBufferElement> const& elements() const 
            { return m_elements; }

    private:
        std::vector<VertexBufferElement> m_elements;
        unsigned int m_stride = 0;
    };
}