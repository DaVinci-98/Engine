#include "Renderer/triangle2D.hpp"
#include "Helpers/logger.hpp"

namespace MyEngine::Renderer
{
    Triangle2D::Triangle2D(float t_ax, float t_bx, float t_cx,
                           float t_ay, float t_by, float t_cy)
    {
        // push various to the vector of vertices
        m_vertices.push_back(t_ax);
        m_vertices.push_back(t_ay);
        m_vertices.push_back(t_bx);
        m_vertices.push_back(t_by);
        m_vertices.push_back(t_cx);
        m_vertices.push_back(t_cy);

        // layout - 2D coordinates
        m_layout.push_back(2);
    }

    bool Triangle2D::addParam(std::vector<float> const& t_params_a, 
                              std::vector<float> const& t_params_b, 
                              std::vector<float> const& t_params_c)
    {
        // Check if the length of added parameters is equal
        if(t_params_a.size() != t_params_b.size() ||
           t_params_a.size() != t_params_c.size())
        {
            Helpers::Logger::log<Triangle2D>(Helpers::Logger::LogType::ERROR,
                "[addParam()]: Lengths of parameters don't match.");
            return false;
        }

        unsigned int oldVertexParamCount = m_vertices.size() / 3;
        size_t size = t_params_a.size();

        unsigned int offsetA = oldVertexParamCount;
        unsigned int offsetB = 2 * oldVertexParamCount + size;
        unsigned int offsetC = 3 * oldVertexParamCount + 2 * size;
        
        m_vertices.insert(m_vertices.begin() + offsetA, t_params_a.begin(), t_params_a.end());
        m_vertices.insert(m_vertices.begin() + offsetB, t_params_b.begin(), t_params_b.end());
        m_vertices.insert(m_vertices.begin() + offsetC, t_params_c.begin(), t_params_c.end());

        // Add the length of the parameter the layout
        m_layout.push_back(size);

        return true;
    }
}