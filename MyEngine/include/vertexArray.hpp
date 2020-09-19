#pragma once

#include "vertexBuffer.hpp"
#include "vertexBufferLayout.hpp"

namespace MyEngine
{
    class VertexArray
    {
    public:
        VertexArray();
        ~VertexArray();

        void bind();
        void unbind();
        bool bound() const { return m_bound; } 

        void addBuffer(VertexBuffer& t_buffer, VertexBufferLayout const& t_layout);
    private:
        void addAttrib(VertexBufferElement const& t_element, 
            unsigned int& t_pos, unsigned int& t_offset, 
            unsigned int t_stride) const;

        unsigned int m_rendererId = 0;
        bool m_bound = false;
    };
}