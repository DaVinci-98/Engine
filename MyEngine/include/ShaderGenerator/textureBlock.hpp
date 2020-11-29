#pragma once

#include "ShaderGenerator/block.hpp"

namespace MyEngine::ShaderGenerator
{
    class TextureBlock : public Block
    {
    public:
        TextureBlock(std::string t_textureUniformName = "u_texture");
    };
}