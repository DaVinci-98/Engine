#pragma once

#include "ShaderGenerator/block.hpp"

namespace MyEngine::ShaderGenerator
{
    /**
     * @brief Block describing rendering of a coloured triangle.
     * 
     */
    class ColourBlock : public Block
    {
    public:
        /**
         * @brief Construct a new ColourBlock object.
         * 
         */
        ColourBlock();
    };
}