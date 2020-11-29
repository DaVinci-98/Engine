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
        bool bound() const { return m_bound; } 

        // Assign buffer with specified layout
        void setBuffer(VertexBuffer& t_buffer, VertexBufferLayout const& t_layout);
        void addBuffer(VertexBuffer& t_buffer, unsigned int t_offset, unsigned int t_vertexSize, VertexBufferLayout const& t_layout);

        void setBuffers(std::vector<std::pair<VertexBuffer, VertexBufferLayout>> t_buffers);
    private:
        void addAttrib(VertexBufferElement const& t_element, 
            unsigned int t_pos, unsigned int t_offset, 
            unsigned int t_stride) const;

        unsigned int m_rendererId = 0;
        bool m_bound = false;
    };
}