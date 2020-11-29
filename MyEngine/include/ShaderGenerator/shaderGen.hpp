#pragma once

#include "ShaderGenerator/block.hpp"

#include <string>
#include <glm/common.hpp>
#include <unordered_map>
#include <vector>

namespace MyEngine::ShaderGenerator
{
    class ShaderGen
    {
    public:
        struct VertexLayoutItem
        {
            std::string m_name;
            int m_position;
            int m_count;
        };

        struct UniformItem
        {
            std::string m_name;
            Block::FieldType m_type;
        };

        std::string makeVertex();
        std::string makeFragment();

        inline void setVersion(std::string t_version)
            { m_version = t_version; }
        inline void setBlocks(std::vector<Block>&& t_blocks)
            { m_blocks = std::move(t_blocks); }

        inline std::vector<VertexLayoutItem>& vertexLayout() 
            { return m_vertexLayout; }
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