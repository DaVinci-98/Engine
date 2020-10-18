#include "glad/glad.h"

#include "indexBuffer.hpp"
#include "glException.hpp"

#include <array>
#include <iostream>

namespace MyEngine::OpenGL
{    
    IndexBuffer::IndexBuffer(std::vector<unsigned int> const& t_data)
        : m_count(t_data.size())
    {
        GL_CALL(glGenBuffers(1, &m_rendererId));
        bind();
        GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_count * sizeof(unsigned int), t_data.data(), GL_STATIC_DRAW));
        unbind();
    }
    IndexBuffer::~IndexBuffer()
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

    void IndexBuffer::bind()
    {
        if(m_bound) return;
        GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererId));
        m_bound = true;
    }

    void IndexBuffer::unbind()
    {
        if(!m_bound) return;
        GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
        m_bound = false;
    }
}