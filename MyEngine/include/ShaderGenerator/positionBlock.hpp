#pragma once

#include "ShaderGenerator/block.hpp"

namespace MyEngine::ShaderGenerator
{
    class PositionBlock : public Block
    {
    public:
        PositionBlock(std::string t_modelUniformName = "u_model", 
                      std::string t_viewUniformName = "u_view",
                      std::string t_projectionUniformName = "u_projection" );
    };
}