#pragma once

#include <array>
#include <any>
#include <vector>

namespace MyEngine
{
    // Abstraction for openGL buffer object.
    // Vertex data is stored into GPU memory.
    class VertexBuffer
    {
    public:
        //t_data - data to be copied into the buffer.
        VertexBuffer(std::vector<float> const& t_data);
        VertexBuffer(std::vector<unsigned int> const& t_data);
        //Frees the buffer
        ~VertexBuffer();

        void bind();
        void unbind();
        bool bound() const { return m_bound; } 
    private:
        unsigned int m_rendererId = 0;
        bool m_bound = false;
    };
}