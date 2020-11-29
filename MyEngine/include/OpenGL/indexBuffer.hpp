#pragma once

#include <array>
#include <vector>

namespace MyEngine::OpenGL
{
    // Abstraction for openGL buffer object.
    // Identifies which vertices belong to a triangle,
    // by their indexes in vertex buffer.
    class IndexBuffer
    {
    public:
        
        IndexBuffer(std::vector<unsigned int> const& t_data);
        ~IndexBuffer();

        void bind();
        void unbind();

        unsigned int count() const { return m_count; } 
    private:
        unsigned int m_rendererId = 0;
        unsigned int m_count = 0;
    };
}