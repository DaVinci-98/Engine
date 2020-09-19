#pragma once

#include <array>
#include <any>
#include <vector>

namespace MyEngine
{
    class VertexBuffer
    {
    public:
        VertexBuffer(std::vector<float> const& t_data);
        VertexBuffer(std::vector<unsigned int> const& t_data);
        ~VertexBuffer();

        void bind();
        void unbind();
        bool bound() const { return m_bound; } 
    private:
        unsigned int m_rendererId = 0;
        bool m_bound = false;
    };
}