#pragma once

#include "ShaderGenerator/block.hpp"

namespace MyEngine::ShaderGenerator
{
    /**
     * @brief Block describing position of a vertex.
     * Has to be used in order to render vertexes with position provided form outside shader.
     * 
     */
    class PositionBlock : public Block
    {
    public:
        /**
         * @brief Construct a new PositionBlock object.
         * Uniform names shouldn't be changed unless these names are required in another block.
         * 
         * @param t_modelUniformName name of a model matrix uniform.
         * @param t_viewUniformName name of a view matrix uniform.
         * @param t_projectionUniformName name of a projection matrix uniform.
         */
        PositionBlock(std::string t_modelUniformName = "u_model", 
                      std::string t_viewUniformName = "u_view",
                      std::string t_projectionUniformName = "u_projection" );
    };
}