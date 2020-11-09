#pragma once

#include <string>
#include <unordered_map>
#include <vector>

namespace MyEngine::ShaderGenerator
{
    class Block
    {
    public:
        enum FieldType
        {
            VEC2,
            VEC3,
            VEC4,
            MAT4,
            SAMPLER2D
        };
        inline std::vector<std::string>& getVertexUniforms()
            { return m_vertexUniforms; }
        inline std::vector<std::string>& getFragmentUniforms()
            { return m_fragmentUniforms; }
        inline std::vector<std::string>& getVertexLocations()
            { return m_vertexLocations; }
        inline std::vector<std::string>& getFragmentLocations()
            { return m_fragmentLocations; }
        inline std::vector<std::string>& getFragmentIns()
            { return m_fragmentIns; }
        inline std::vector<std::string>& getVertexOuts()
            { return m_vertexOuts; }
        inline std::vector<std::string>& getVertexCodeLines()
            { return m_vertexCodeLines; }
        inline std::vector<std::string>& getFragmentCodeLines()
            { return m_fragmentCodeLines; }
    protected:
        inline void addVertexUniform(std::string t_name, FieldType t_type)
            { m_vertexUniforms.push_back(getTypeString(t_type) + " " + t_name); }
        inline void addFragmentUniform(std::string t_name, FieldType t_type)
            { m_fragmentUniforms.push_back(getTypeString(t_type) + " " + t_name); }
        inline void addVertexLocation(std::string t_name, FieldType t_type)
            { m_vertexLocations.push_back(getTypeString(t_type) + " " + t_name); }
        inline void addFragmentLocation(std::string t_name, FieldType t_type)
            { m_fragmentLocations.push_back(getTypeString(t_type) + " " + t_name); }
        inline void addFragmentIn(std::string t_name, FieldType t_type)
            { m_fragmentIns.push_back(getTypeString(t_type) + " " + t_name); }
        inline void addVertexOut(std::string t_name, FieldType t_type)
            { m_vertexOuts.push_back(getTypeString(t_type) + " " + t_name); }
        inline void addVertexCodeLine(std::string t_code)
            { m_vertexCodeLines.push_back(t_code); }
        inline void addFragmentCodeLine(std::string t_code)
            { m_fragmentCodeLines.push_back(t_code); }
    private:
        std::string getTypeString(FieldType t_type);
        std::vector<std::string> m_vertexUniforms;
        std::vector<std::string> m_fragmentUniforms;
        std::vector<std::string> m_vertexLocations;
        std::vector<std::string> m_fragmentLocations;
        std::vector<std::string> m_fragmentIns;
        std::vector<std::string> m_vertexOuts;
        std::vector<std::string> m_vertexCodeLines;
        std::vector<std::string> m_fragmentCodeLines;
    };
}