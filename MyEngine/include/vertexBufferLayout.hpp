#pragma once

#include <vector>
#include <GL/glew.h>
#include <iostream>

namespace MyEngine
{
    struct VertexBufferElement
    {
        unsigned int count;
        GLenum type;
        unsigned int typeSize;
        GLenum normalized;
    };

    class VertexBufferLayout
    {
    public:
        VertexBufferLayout() { };

        template<typename T> void push(size_t m_count);

        unsigned int stride() const { return m_stride; }
        unsigned int numElements() const { return m_elements.size(); }
        VertexBufferElement const& elementAt(unsigned int t_pos) const { return m_elements.at(t_pos); }
        std::vector<VertexBufferElement> const& elements() const { return m_elements; }

    private:
        std::vector<VertexBufferElement> m_elements;
        unsigned int m_stride = 0;
    };
}