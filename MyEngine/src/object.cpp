#include "glad/glad.h"

#include "object.hpp"
#include "vertexBuffer.hpp"
#include "vertexBufferLayout.hpp"

#include <algorithm>
#include <iostream>

namespace MyEngine
{
    bool Object::bake()
    {   
        auto triangles(std::move(m_triangles));
        for (auto const& triangle : triangles) 
            bakeTriangle(triangle);

        unsigned int bufferCount = m_buffer.size() * m_buffer.front().size();
        std::vector<float> buffer;
        for (auto const& row : m_buffer) 
            buffer.insert(buffer.end(), row.begin(), row.end());

        try
        {
            m_vertexArray = std::make_unique<VertexArray>();
            m_buffers.push_back(std::make_unique<VertexBuffer>(buffer));

            VertexBufferLayout layout;

            auto triangleLayout = triangles.front()->layout();

            for (auto const& a : triangleLayout)
                layout.push<float>(a);


            m_vertexArray -> addBuffer(*m_buffers.back(), layout);
            m_indexBuffer = std::make_unique<IndexBuffer>(m_indecies);
            
            std::vector<ShaderFile> files 
            {
                ShaderFile {"Sandbox/res/shaders/basicVertex.shader", GL_VERTEX_SHADER },
                ShaderFile {"Sandbox/res/shaders/basicFragment.shader", GL_FRAGMENT_SHADER }
            };
            m_shader = std::make_unique<Shader>(files);
        }
        catch(GlException &e)
        {
            e.printErrors();
            return false;
        }

        return true;
    }
}