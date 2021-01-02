#pragma once

#include "ShaderGenerator/block.hpp"

namespace MyEngine::ShaderGenerator
{
    /**
     * @brief Block describing rendering of a textured triangle.
     * 
     */
    class TextureBlock : public Block
    {
    public:
        /**
         * @brief Construct a new TextureBlock object.
         * Uniform name shouldn't be changed unless this name is required in another block.
         * 
         * @param t_textureUniformName name of a texture uniform, used to change active texture slots.
         */
        TextureBlock(std::string t_textureUniformName = "u_texture");
    };
}