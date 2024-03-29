#include "Renderer/material.hpp"
#include "Logger/logger.hpp"

#include <algorithm>
#include <iterator>

namespace MyEngine::Renderer
{
    Material:: Material(std::shared_ptr<Shader> t_shader):
        m_shader(t_shader) 
    { 
        // if(isColour())
        //     Logger::Logger::log<Material>() -> info(
        //    "[Colour] [Init]: Done");
        // else
        //     Logger::Logger::log<Material>() -> info(
        //    "[Texture] [Init]: Done");
    }

    Material::~Material()
    {
        if(isColour())
            Logger::Logger::log<Material>() -> info(
           "[Colour] [Destroy]: Done");
        else
            Logger::Logger::log<Material>() -> info( 
           "[Texture] [Destroy]: Done");
    }

    unsigned int Material::setTextureBuffer(std::vector<float> && t_vertices, std::vector<unsigned int> && t_indicies, std::string t_path, unsigned int t_stride)
    {
        if(!m_shader -> usesTexture())
        {
            Logger::Logger::log<Material>() -> error(
                "[setTextureBuffer()]: Material doesn't render triangles with textures.");
            return 0;
        }
        if(m_stride != 0) clear();
        m_stride = t_stride;

        m_vertices = std::move(t_vertices);
        m_indicies = std::move(t_indicies);

        m_vertexBuffer = std::make_unique<OpenGL::VertexBuffer>(m_vertices);
        m_layout = std::make_unique<OpenGL::VertexBufferLayout>();

        m_layout -> push<float>(m_stride);

        m_texture = std::make_unique<OpenGL::Texture>(t_path);
        return 0;
    }

    void Material::setColour(glm::vec4&& t_colour)
    {
        if(m_shader -> usesTexture())
        {
            Logger::Logger::log<Material>() -> error(
                "[setColour()]: Material doesn't render triangles with flat colour.");
            return;
        }

        m_shader -> setVec4Uniform(Shader::COLOUR_UNIFORM, t_colour, false);
    }

    unsigned int Material::setTexture(std::vector<Triangle2D> && t_triangles, std::string t_path, bool t_colapse)
    {
        if(!m_shader -> usesTexture())
        {
            Logger::Logger::log<Material>() -> error(
                "[setTextureBuffer()]: Material doesn't render triangles with textures.");
            return 0;
        }
        if(m_stride != 0) clear();

        insertTriangles(std::move(t_triangles), true, t_colapse);

        m_vertexBuffer = std::make_unique<OpenGL::VertexBuffer>(m_vertices);
        m_layout = std::make_unique<OpenGL::VertexBufferLayout>();

        m_layout -> push<float>(m_stride);

        m_texture = std::make_unique<OpenGL::Texture>(t_path);
        return 0;
    }

    void Material::insertTriangles(std::vector<Triangle2D>&& t_triangles, bool t_useIndicies, bool t_colapse)
    {
        m_stride = static_cast<unsigned int>(t_triangles[0].vertices().size() / 3);

        for(auto& triangle : t_triangles)
        {
            insertVertex(std::vector<float>(triangle.vertices().begin(),              triangle.vertices().begin() +   m_stride), t_useIndicies, t_colapse);
            insertVertex(std::vector<float>(triangle.vertices().begin() +   m_stride, triangle.vertices().begin() + 2*m_stride), t_useIndicies, t_colapse);
            insertVertex(std::vector<float>(triangle.vertices().begin() + 2*m_stride, triangle.vertices().begin() + 3*m_stride), t_useIndicies, t_colapse);
        }
    }

    void Material::insertVertex(std::vector<float>&& t_vertex, bool t_useIndicies, bool t_colapse)
    {
        int index = -1;
        if(t_useIndicies && t_colapse) index = findVertex(t_vertex);

        if(index < 0)
        {
            m_vertices.insert(m_vertices.end(),
                std::make_move_iterator(t_vertex.begin()),
                std::make_move_iterator(t_vertex.end()));
            if(t_useIndicies)
            {
                unsigned int new_index = static_cast<unsigned int>(m_vertices.size() / m_stride) - 1;
                m_indicies.push_back(new_index);
            }
        }
        else if(t_useIndicies)
            m_indicies.push_back(index);        
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
            if(begin < m_vertices.end()) begin++;
        }
        return -1;
    }

    void Material::bind()
    {
        if(m_bound) return;
        m_bound = true;

        if(m_shader -> usesTexture())
            m_shader -> setTextureUniform(Shader::TEXTURE_UNIFORM, 0);

        m_shader -> bind();
        
        if(m_shader -> usesTexture())
            m_texture -> bind(0);
    }

    void Material::unbind()
    {
        if(!m_bound) return;
        m_bound = false;

        m_shader -> unbind();
        if(m_shader -> usesTexture())
        {
            m_vertexBuffer -> unbind();
            m_texture -> unbind();
        }
    }

    void Material::clear()
    {
        m_stride = 0;

        unbind();

        m_vertexBuffer.reset();
        m_layout.reset();
        if(m_shader -> usesTexture())
            m_texture.reset();

        m_vertices.clear();
        m_indicies.clear();
    }
}