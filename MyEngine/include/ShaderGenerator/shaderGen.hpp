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
        void setVersion(std::string t_version)
            { m_version = t_version; }
        void addBlock(Block&& t_block)
            { m_blocks.push_back(std::move(t_block)); }
        std::string makeVertex() const;
        std::string makeFragment() const;
    private:
        std::vector<Block> m_blocks;
        std::string m_version = "460";
    };
}