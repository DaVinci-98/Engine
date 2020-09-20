#include "vertexBuffer.hpp"
#include "glException.hpp"
#include "glad/glad.h"

#include <array>
#include <iostream>

namespace MyEngine
{   
    VertexBuffer::VertexBuffer(std::vector<float>const& t_data)
    {
        GL_CALL(glGenBuffers(1, &m_rendererId));
        bind();
        GL_CALL(glBufferData(GL_ARRAY_BUFFER, t_data.size() * sizeof(float), t_data.data(), GL_STATIC_DRAW));
        unbind();
    }

    VertexBuffer::VertexBuffer(std::vector<unsigned int>const& t_data)
    {
        GL_CALL(glGenBuffers(1, &m_rendererId));
        bind();
        GL_CALL(glBufferData(GL_ARRAY_BUFFER, t_data.size() * sizeof (unsigned int), t_data.data(), GL_STATIC_DRAW));
        unbind();
    }

    VertexBuffer::~VertexBuffer()
    {
        try
        {
            GL_CALL(glDeleteBuffers(1, &m_rendererId));
        }
        catch(GlException const& e)
        {
            e.printErrors();
        }        
    }

    void VertexBuffer::bind()
    {
        if(m_bound) return;
        GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, m_rendererId));
        m_bound = true;
    }

    void VertexBuffer::unbind()
    {
        if(!m_bound) return;
        GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
        m_bound = false;
    }
}