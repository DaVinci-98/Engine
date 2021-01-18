#pragma once

#include "ShaderGenerator/block.hpp"

#include <glm/common.hpp>
#include <vector>

namespace MyEngine::ShaderGenerator
{
    /**
     * @brief Class for generating shader strings.
     * 
     */
    class ShaderGen
    {
    public:
        /**
         * @brief Item in vertex layout list in the shader.
         * 
         */
        struct VertexLayoutItem
        {
            std::string m_name;
            int m_position;
            int m_count;
        };

        /**
         * @brief Item in uniform list in the shader.
         * 
         */
        struct UniformItem
        {
            std::string m_name;
            Block::FieldType m_type;
        };

        /**
         * @brief Return vertex shader.
         * 
         */
        std::string makeVertex();
        /**
         * @brief Return fragment shader.
         * 
         */
        std::string makeFragment();

        /**
         * @brief Set the version string.
         * 
         * @param t_version new version
         */
        inline void setVersion(std::string t_version)
            { m_version = t_version; }
        /**
         * @brief Set vector of Block objects.
         * Blocks are used to build shaders.
         * 
         */
        inline void setBlocks(std::vector<Block>&& t_blocks)
            { m_blocks = std::move(t_blocks); }

        /**
         * @brief Get a reference to vector of VertexLayoutItem objects.
         * 
         */
        inline std::vector<VertexLayoutItem>& vertexLayout() 
            { return m_vertexLayout; }
        /**
         * @brief Get a reference to vector of UniformItem objects.
         * 
         */
        inline std::vector<UniformItem>& uniforms() 
            { return m_unifroms; }
    private:
        std::string pieceOutCode(
            std::string& t_version,
            std::stringstream& t_locations, 
            std::stringstream& t_uniforms,
            std::stringstream& t_inOuts,
            std::stringstream& t_code);

        std::vector<VertexLayoutItem> m_vertexLayout;
        std::vector<UniformItem> m_unifroms;
        std::vector<Block> m_blocks;
        std::string m_version = "460";
    };
}