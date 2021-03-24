#include "glad/gl.h"

#include "OpenGL/vertexArray.hpp"
#include "OpenGL/glException.hpp"

#include <algorithm>

namespace MyEngine::OpenGL
{
    VertexArray::VertexArray()
    {
        GL_CALL(glGenVertexArrays(1, &m_rendererId));
    }

    VertexArray::~VertexArray()
    {
        try
        {
            GL_CALL(glDeleteVertexArrays(1, &m_rendererId));
        }
        catch(GlException const& e)
        {
            e.printErrors();
        }        
    }

    void VertexArray::bind()
    {
        GL_CALL(glBindVertexArray(m_rendererId));
    }

    void VertexArray::unbind()
    {
        GL_CALL(glBindVertexArray(0));
    }
    
    unsigned int VertexArray::setBuffer(VertexBuffer& t_buffer, VertexBufferLayout const& t_layout, unsigned int t_firstPos)
    {
        t_buffer.bind();
        this -> bind();

        unsigned int offset = 0;
        unsigned int pos = t_firstPos;

        for(auto const& element : t_layout.elements()) 
        {
            addAttrib(element, pos, offset, t_layout.stride());
            offset += element.count * element.typeSize;
            pos++;
        }

        t_buffer.unbind();
        this -> unbind();
        return pos;
    }

    void VertexArray::addAttrib(VertexBufferElement const& t_element, 
        unsigned int t_pos, unsigned int t_offset, 
        unsigned int t_stride) const
    {
        //workaround for openGL's weird pointer for offset
        void const* offset = static_cast<char const*>(0) + t_offset;

        GL_CALL(glEnableVertexAttribArray(t_pos));
        // Every value is converted to float when accessed, 
        // Normalize puts int values into [-1,1] / [0,1] range,
        // To get int values inside shader use glVertexAttribIPointer,
        // To get double values inside shader use glVertexAttribLPointer
        GL_CALL(glVertexAttribPointer(t_pos, t_element.count, t_element.type, t_element.normalized, t_stride, offset));
    }
}