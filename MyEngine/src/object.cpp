#include "glad/glad.h"

#include "openGL/glException.hpp"
#include "object.hpp"
#include "openGL/vertexBuffer.hpp"
#include "openGL/vertexBufferLayout.hpp"

#include <algorithm>
#include <iostream>

namespace MyEngine
{
    bool Object::toVAO()
    {   
        // Move triangles into the function
        // Change triangle data into buffers
        auto triangles(std::move(m_triangles));
        for (auto const& triangle : triangles) 
            triangleToVAO(triangle);

        // Push the buffers from individual vertecies into single one
        std::vector<float> buffer;
        for (auto const& row : m_buffer) 
            buffer.insert(buffer.end(), row.begin(), row.end());

        try
        {
            m_vertexArray = std::make_unique<VertexArray>();
            m_buffers.push_back(std::make_unique<VertexBuffer>(buffer));
            VertexBufferLayout layout;

            // Get a layout of vertecies in traingles
            auto triangleLayout = triangles.front()->layout();

            // Assume all values are float
            for (auto const& a : triangleLayout)
                layout.push<float>(a);

            // Make vertex array and index buffer
            m_vertexArray -> addBuffer(*m_buffers.back(), layout);
            m_indexBuffer = std::make_unique<IndexBuffer>(m_indecies);
            
            // Load shaders
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