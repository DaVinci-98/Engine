#include "vertexBufferLayout.hpp"
#include <exception>
#include <GL/glew.h>
#include <iostream>

namespace MyEngine
{
    template<typename T> 
    void VertexBufferLayout::push(size_t t_count)
    {
        throw std::exception();
    }

    template<>
    void VertexBufferLayout::push<float>(size_t t_count)
    {
        VertexBufferElement element;
        element.count = t_count;
        element.type = GL_FLOAT;
        element.normalized = GL_FALSE;
        element.typeSize = sizeof(GLfloat);

        m_elements.push_back(element);
        m_stride += element.typeSize * t_count;
    }

    template<>
    void VertexBufferLayout::push<unsigned int>(size_t t_count)
    {
        VertexBufferElement element;
        element.count = t_count;
        element.type = GL_UNSIGNED_INT;
        element.normalized = GL_FALSE;
        element.typeSize = sizeof(GLuint);

        m_elements.push_back(element);
        m_stride += element.typeSize * t_count;
    }

    template<>
    void VertexBufferLayout::push<unsigned char>(size_t t_count)
    {
        VertexBufferElement element;
        element.count = t_count;
        element.type = GL_UNSIGNED_BYTE;
        element.normalized = GL_TRUE;
        element.typeSize = sizeof(GLubyte);

        m_elements.push_back(element);
        m_stride += element.typeSize * t_count;
    }
}