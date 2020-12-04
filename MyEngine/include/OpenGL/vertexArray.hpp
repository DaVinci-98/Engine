#pragma once

#include "OpenGL/vertexBuffer.hpp"
#include "OpenGL/vertexBufferLayout.hpp"

#include <memory>

namespace MyEngine::OpenGL
{
    // Abstraction for openGL buffer object.
    // Vertex data with applied layout
    class VertexArray
    {
    public:
        VertexArray();
        ~VertexArray();

        void bind();
        void unbind();

        // Assign buffer with specified layout
        unsigned int setBuffer(VertexBuffer& t_buffer, VertexBufferLayout const& t_layout, unsigned int t_firstPos = 0);
    private:
        void addAttrib(VertexBufferElement const& t_element, 
            unsigned int t_pos, unsigned int t_offset, 
            unsigned int t_stride) const;

        unsigned int m_rendererId = 0;
    };
}