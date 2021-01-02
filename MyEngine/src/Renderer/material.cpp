#include "Renderer/material.hpp"
#include "ShaderGenerator/shaderGen.hpp"
#include "ShaderGenerator/positionBlock.hpp"
#include "ShaderGenerator/textureBlock.hpp"
#include "ShaderGenerator/colourBlock.hpp"
#include "Helpers/logger.hpp"

#include <algorithm>
#include <iterator>
#include <iostream>

namespace MyEngine::Renderer
{
    unsigned int Material::setTextureBuffer(std::vector<float> && t_vertices, std::vector<unsigned int> && t_indecies, std::string t_path, unsigned int t_stride)
    {
        if(!m_shader->usesTexture())
        {
            Helpers::Logger::log<Material>() -> error("[setTextureBuffer()]: Material deosn't render triangles with textures.");
            return 0;
        }
        if(m_stride != 0) clear();
        m_stride = t_stride;

        m_vertices = std::move(t_vertices);
        m_indecies = std::move(t_indecies);

        m_vertexBuffer = std::make_unique<OpenGL::VertexBuffer>(m_vertices);
        m_layout = std::make_unique<OpenGL::VertexBufferLayout>();

        m_layout -> push<float>(m_stride);

        unsigned int id = addTexture(t_path);
        setTextureId(id);
        return id;
    }

    unsigned int Material::addTexture(std::string const& t_path)
    {
        unsigned int id = m_highestTextureId++;
        m_textures.insert(std::pair<unsigned int, OpenGL::Texture>(id, OpenGL::Texture(t_path)));
        return id;
    }

    void Material::setColour(glm::vec4&& t_colour)
    {
        if(m_shader->usesTexture())
        {
            Helpers::Logger::log<Material>() -> error("[setColour()]: Material deosn't render triangles with flat colour.");
            return;
        }

        m_shader -> setVec4Uniform(Shader::COLOUR_UNIFORM, t_colour, true);
    }

    unsigned int Material::setTexture(std::vector<Triangle2D> && t_triangles, std::string t_path)
    {
        if(!m_shader->usesTexture())
        {
            Helpers::Logger::log<Material>() -> error("[setTextureBuffer()]: Material deosn't render triangles with textures.");
            return 0;
        }
        if(m_stride != 0) clear();

        insertTriangles(std::move(t_triangles), true);

        m_vertexBuffer = std::make_unique<OpenGL::VertexBuffer>(m_vertices);
        m_layout = std::make_unique<OpenGL::VertexBufferLayout>();

        m_layout -> push<float>(m_stride);

         unsigned int id = addTexture(t_path);
        setTextureId(id);
        return id;
    }

    void Material::insertTriangles(std::vector<Triangle2D>&& t_triangles, bool t_useIndecies)
    {
        m_stride = static_cast<unsigned int>(t_triangles[0].vertices().size() / 3);

        for(auto& triangle : t_triangles)
        {
            insertVertex(std::vector<float>(triangle.vertices().begin(),              triangle.vertices().begin() +   m_stride), t_useIndecies);
            insertVertex(std::vector<float>(triangle.vertices().begin() +   m_stride, triangle.vertices().begin() + 2*m_stride), t_useIndecies);
            insertVertex(std::vector<float>(triangle.vertices().begin() + 2*m_stride, triangle.vertices().begin() + 3*m_stride), t_useIndecies);
        }
    }

    void Material::insertVertex(std::vector<float>&& t_vertex, bool t_useIndecies)
    {
        int index = -1;
        if(t_useIndecies) index = findVertex(t_vertex);

        if(index < 0)
        {
            m_vertices.insert(m_vertices.end(),
                std::make_move_iterator(t_vertex.begin()),
                std::make_move_iterator(t_vertex.end()));
            if(t_useIndecies)
            {
                unsigned int new_index = static_cast<unsigned int>(m_vertices.size() / m_stride) - 1;
                m_indecies.push_back(new_index);
            }
        }
        else if(t_useIndecies)
            m_indecies.push_back(index);        
    }

    int Material::findVertex(std::vector<float>& t_vertex)
    {
        auto begin = m_vertices.begin();
        while(begin < m_vertices.end())
        {
            begin = std::search(begin, m_vertices.end(), t_vertex.begin(), t_vertex.end());
            int dist = std::distance(m_vertices.begin(), begin);
            if(dist%m_stride == 0 && begin < m_vertices.end())
                return static_cast<int>(dist / m_stride);
            begin++;
        }
        return -1;
    }

    void Material::bind()
    {
        if(m_bound) return;
        m_bound = true;

        if(m_shader->usesTexture())
            m_shader -> setTextureUniform(Shader::TEXTURE_UNIFORM, m_currentTextureId);

        m_shader -> bind();
        
        if(m_shader->usesTexture())
            for(auto& [id, texture] : m_textures)
                texture.bind(id);
    }

    void Material::unbind()
    {
        if(!m_bound) return;
        m_bound = false;

        m_shader -> unbind();
        if(m_shader->usesTexture())
        {
            m_vertexBuffer -> unbind();
            for(auto& [id, texture] : m_textures)
                texture.unbind();
        }
    }

    void Material::clear()
    {
        m_stride = 0;

        unbind();

        m_vertexBuffer.reset();
        m_layout.reset();
        if(m_shader->usesTexture())
            m_textures.clear();

        m_vertices.clear();
        m_indecies.clear();
    }
}