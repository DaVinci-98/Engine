#include "object2D.hpp"
#include "zip.hpp"
#include <iostream>
#include <algorithm>

namespace MyEngine
{
    bool Object2D::pushTriangle(Triangle2D const& t_triangle)
    {
        m_triangles.push_back(std::make_unique<Triangle2D>(t_triangle));
        return true;
    }

    bool Object2D::mapTexture(std::vector<Triangle2D> const& t_coordinates, std::string const& path)
    {
        if(t_coordinates.size() != m_triangles.size()) return false;

        bool textured = m_texture != nullptr;
        if(textured) m_texture.reset();
        m_texture = std::make_unique<Texture>(path);


        unsigned int tex_stride = t_coordinates.front().vertecies().size() / 3;
        
        auto zip = std::move(Zip::Zip2(t_coordinates, m_triangles));
        for(auto const& [coordinates, triangle] : zip)
        {
            float tex_a_x = coordinates.get().vertecies()[0];
            float tex_a_y = coordinates.get().vertecies()[1];
            float tex_b_x = coordinates.get().vertecies()[2];
            float tex_b_y = coordinates.get().vertecies()[3];
            float tex_c_x = coordinates.get().vertecies()[4];
            float tex_c_y = coordinates.get().vertecies()[5];
            triangle.get()->mapTexture(tex_a_x, tex_b_x, tex_c_x,
                                       tex_a_y, tex_b_y, tex_c_y);
        }

        // for(int i = 0; i < t_coordinates.size(); i++)
        // {
        //     float tex_a_x = t_coordinates[i].vertecies()[0];
        //     float tex_a_y = t_coordinates[i].vertecies()[1];
        //     float tex_b_x = t_coordinates[i].vertecies()[2];
        //     float tex_b_y = t_coordinates[i].vertecies()[3];
        //     float tex_c_x = t_coordinates[i].vertecies()[4];
        //     float tex_c_y = t_coordinates[i].vertecies()[5];
        //     m_triangles[i]->mapTexture(tex_a_x, tex_b_x, tex_c_x,
        //                                tex_a_y, tex_b_y, tex_c_y);
        // }
        return true;
    }

    void Object2D::bakeTriangle(std::unique_ptr<Triangle> const& t_triangle)
    {
        unsigned int stride = t_triangle->vertecies().size() / 3;
        std::vector<float> buffer_a(
            t_triangle->vertecies().begin(),
            t_triangle->vertecies().begin() + stride);
        std::vector<float> buffer_b(
            t_triangle->vertecies().begin() + stride,
            t_triangle->vertecies().begin() + 2 * stride);
        std::vector<float> buffer_c(
            t_triangle->vertecies().begin() + 2 * stride,
            t_triangle->vertecies().begin() + 3 * stride);

        saveVertex(buffer_a);
        saveVertex(buffer_b);
        saveVertex(buffer_c);
    }

    void Object2D::saveVertex(std::vector<float> const& t_vertex)
    {
        auto sameVertex = [&](std::vector<float> const& a) -> bool
        {
            return a[0] == t_vertex[0] && a[1] == t_vertex[1];
        };
        auto index = std::find_if(m_buffer.begin(), m_buffer.end(), sameVertex);

        if(index == m_buffer.end())
        {
            m_buffer.push_back(t_vertex);
            m_indecies.push_back(m_buffer.size() - 1);
        }
        else
        {
            m_indecies.push_back(index - m_buffer.begin());
        }
    }
}