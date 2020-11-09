#pragma once

#include <vector>
#include <iostream>

namespace MyEngine::OpenGL
{
    // Layout of vertecies in vertex buffer
    struct VertexBufferElement
    {
        unsigned int count;
        unsigned int type;
        unsigned int typeSize;
        unsigned int normalized;
    };

    // Layout of the Vertex buffer
    class VertexBufferLayout
    {
    public:
        VertexBufferLayout() { };

        // Add t_count of values of type T to the layout
        template<typename T> void push(size_t t_count);

        //! TODO: bool operator==();

        unsigned int stride() const { return m_stride; }
        unsigned int numElements() const { return m_elements.size(); }
        VertexBufferElement const& elementAt(unsigned int t_pos) const { return m_elements.at(t_pos); }
        std::vector<VertexBufferElement> const& elements() const { return m_elements; }

    private:
        std::vector<VertexBufferElement> m_elements;
        unsigned int m_stride = 0;
    };
}