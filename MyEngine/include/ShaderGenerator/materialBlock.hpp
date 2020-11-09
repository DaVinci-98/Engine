#pragma once

#include "ShaderGenerator/block.hpp"

namespace MyEngine::ShaderGenerator
{
    class MaterialBlock : public Block
    {
    public:
        enum MaterialType
        {
            TEXTURE,
            COLOUR
        };
        MaterialBlock(MaterialType t_type);
    };
}