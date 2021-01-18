#pragma once

#include <string>
#include <unordered_map>
#include <vector>

namespace MyEngine::ShaderGenerator
{
    /**
     * @brief Blocks describe one functionality in shader.
     * Derive to make a specified functionality for rendering.
     * 
     * For example Block can describe texture/colour rendering.
     * 
     */
    class Block
    {
    public:
        /**
         * @brief Type of the uniform or location in shader.
         * 
         */
        enum FieldType
        {
            VEC2,
            VEC3,
            VEC4,
            MAT4,
            SAMPLER2D
        };

        /**
         * @brief Turn FieldType to string.
         * 
         */
        static std::string getTypeString(FieldType t_type);
        /**
         * @brief Get size in bytes of a FieldType.
         * 
         */
        static int getTypeSize(FieldType t_type);
        /**
         * @brief Get uniforms in vertex shader.
         * 
         * @return reference to std::vector of std::tuple of FieldType,std::string  
         */
        inline std::vector<std::tuple<FieldType,std::string>>& getVertexUniforms()
            { return m_vertexUniforms; }
        /**
         * @brief Get uniforms in fragment shader.
         * 
         * @return reference to std::vector of std::tuple of FieldType,std::string  
         */
        inline std::vector<std::tuple<FieldType,std::string>>& getFragmentUniforms()
            { return m_fragmentUniforms; }
        /**
         * @brief Get locations in vertex shader.
         * 
         * @return reference to std::vector of std::tuple of FieldType,std::string  
         */
        inline std::vector<std::tuple<FieldType,std::string>>& getVertexLocations()
            { return m_vertexLocations; }
        /**
         * @brief Get locations in fragment shader.
         * 
         * @return reference to std::vector of std::tuple of FieldType,std::string  
         */
        inline std::vector<std::tuple<FieldType,std::string>>& getFragmentLocations()
            { return m_fragmentLocations; }
        /**
         * @brief Get "In" fields in fragment shader.
         * 
         * @return reference to std::vector of std::tuple of FieldType,std::string  
         */
        inline std::vector<std::tuple<FieldType,std::string>>& getFragmentIns()
            { return m_fragmentIns; }
        /**
         * @brief Get "out" fields in vertex shader.
         * 
         * @return reference to std::vector of std::tuple of FieldType,std::string  
         */
        inline std::vector<std::tuple<FieldType,std::string>>& getVertexOuts()
            { return m_vertexOuts; }
        /**
         * @brief Get code lines in main function in vertex shader.
         * 
         * @return reference to std::vector of std::tuple of FieldType,std::string  
         */
        inline std::vector<std::string>& getVertexCodeLines()
            { return m_vertexCodeLines; }
        /**
         * @brief Get code lines in main function in fragment shader.
         * 
         * @return reference to std::vector of std::tuple of FieldType,std::string  
         */
        inline std::vector<std::string>& getFragmentCodeLines()
            { return m_fragmentCodeLines; }

    protected:
        /**
         * @brief Add uniform in vertex shader.
         * 
         */
        inline void addVertexUniform(std::string t_name, FieldType t_type)
            { m_vertexUniforms.push_back(std::make_tuple(t_type, t_name)); }
        /**
         * @brief Add uniform in fragment shader.
         * 
         */
        inline void addFragmentUniform(std::string t_name, FieldType t_type)
            { m_fragmentUniforms.push_back(std::make_tuple(t_type, t_name)); }
        /**
         * @brief Add location in vertex shader.
         * 
         */
        inline void addVertexLocation(std::string t_name, FieldType t_type)
            { m_vertexLocations.push_back(std::make_tuple(t_type, t_name)); }
        /**
         * @brief Add location in fragment shader.
         * 
         */
        inline void addFragmentLocation(std::string t_name, FieldType t_type)
            { m_fragmentLocations.push_back(std::make_tuple(t_type, t_name)); }
        /**
         * @brief Add "In" field in fragment shader.
         * 
         */
        inline void addFragmentIn(std::string t_name, FieldType t_type)
            { m_fragmentIns.push_back(std::make_tuple(t_type, t_name)); }
        /**
         * @brief Add "out" field in vertex shader.
         * 
         */
        inline void addVertexOut(std::string t_name, FieldType t_type)
            { m_vertexOuts.push_back(std::make_tuple(t_type, t_name)); }
        /**
         * @brief Add code line in main function in vertex shader.
         * 
         */
        inline void addVertexCodeLine(std::string t_code)
            { m_vertexCodeLines.push_back(t_code); }
        /**
         * @brief Add code line in main function in fragment shader.
         * 
         */
        inline void addFragmentCodeLine(std::string t_code)
            { m_fragmentCodeLines.push_back(t_code); }

    private:
        std::vector<std::tuple<FieldType,std::string>> m_vertexUniforms;
        std::vector<std::tuple<FieldType,std::string>> m_fragmentUniforms;
        std::vector<std::tuple<FieldType,std::string>> m_vertexLocations;
        std::vector<std::tuple<FieldType,std::string>> m_fragmentLocations;
        std::vector<std::tuple<FieldType,std::string>> m_fragmentIns;
        std::vector<std::tuple<FieldType,std::string>> m_vertexOuts;
        std::vector<std::string> m_vertexCodeLines;
        std::vector<std::string> m_fragmentCodeLines;
    };
}