#include "triangle2D.hpp"

namespace MyEngine
{
    Triangle2D::Triangle2D(float t_ax, float t_bx, float t_cx,
                           float t_ay, float t_by, float t_cy)
    {
        // push various to the vector of vertecies
        m_vertecies.push_back(t_ax);
        m_vertecies.push_back(t_ay);
        m_vertecies.push_back(t_bx);
        m_vertecies.push_back(t_by);
        m_vertecies.push_back(t_cx);
        m_vertecies.push_back(t_cy);

        // layout - 2D coordinates
        m_layout.push_back(2);
        m_textured = false;
    }

    void Triangle2D::mapTexture(float t_tex_ax, float t_tex_bx, float t_tex_cx,
                                float t_tex_ay, float t_tex_by, float t_tex_cy)
    {
        if(m_textured)
        {
            unsigned int offset = m_vertecies.size() / 3;

            // Textured coordinates are required to be the second parameter
            // [x, y, tex_x, tex_y, ... ]
            m_vertecies[2] = t_tex_ax;
            m_vertecies[3] = t_tex_ay;

            m_vertecies[2 + offset] = t_tex_ax;
            m_vertecies[3 + offset] = t_tex_ay;

            m_vertecies[2 + 2 * offset] = t_tex_ax;
            m_vertecies[3 + 2 * offset] = t_tex_ay;
        }
        else
        {
            std::vector<float> a {t_tex_ax, t_tex_ay};
            std::vector<float> b {t_tex_bx, t_tex_by};
            std::vector<float> c {t_tex_cx, t_tex_cy};

            if(m_layout.size() == 1)
            {
                // If coordinates are the only paramter, texture coorinates can be treated as any other parameter
                bool added = this -> addParam(a, b, c);
            }
            else
            {
                // There are parameters beside coordinates, 
                // so the texture coordinates have to be inserted before them
                unsigned int oldVertexParamCount = m_vertecies.size() / 3;
                unsigned int offsetA = 2;
                unsigned int offsetB = 2 + oldVertexParamCount + 2;
                unsigned int offsetC = 2 + 2 * oldVertexParamCount + 2 * 2;
                
                m_vertecies.insert(m_vertecies.begin() + offsetA, a.begin(), a.end());
                m_vertecies.insert(m_vertecies.begin() + offsetB, b.begin(), b.end());
                m_vertecies.insert(m_vertecies.begin() + offsetC, c.begin(), c.end());

                // Texture coordinates are 2D
                m_layout.push_back(2);
            }
        }
        m_textured = true;
    }

    bool Triangle2D::addParam(std::vector<float> const& t_params_a, 
                              std::vector<float> const& t_params_b, 
                              std::vector<float> const& t_params_c)
    {
        // Check if the length of added parameters is equal
        if(t_params_a.size() != t_params_b.size() ||
           t_params_a.size() != t_params_c.size()) return false;

        unsigned int oldVertexParamCount = m_vertecies.size() / 3;
        size_t size = t_params_a.size();

        unsigned int offsetA = oldVertexParamCount;
        unsigned int offsetB = 2 * oldVertexParamCount + size;
        unsigned int offsetC = 3 * oldVertexParamCount + 2 * size;
        
        m_vertecies.insert(m_vertecies.begin() + offsetA, t_params_a.begin(), t_params_a.end());
        m_vertecies.insert(m_vertecies.begin() + offsetB, t_params_b.begin(), t_params_b.end());
        m_vertecies.insert(m_vertecies.begin() + offsetC, t_params_c.begin(), t_params_c.end());

        // Add the length of the parameter the layout
        m_layout.push_back(size);

        return true;
    }
}