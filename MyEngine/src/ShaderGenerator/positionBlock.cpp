#include "ShaderGenerator/positionBlock.hpp"

namespace MyEngine::ShaderGenerator
{
    PositionBlock::PositionBlock(std::string t_modelUniformName, std::string t_viewUniformName,std::string t_projectionUniformName)
    {
        addVertexLocation("position", FieldType::VEC4);
        addVertexUniform(t_modelUniformName, FieldType::MAT4);
        addVertexUniform(t_viewUniformName, FieldType::MAT4);
        addVertexUniform(t_projectionUniformName, FieldType::MAT4);
        addVertexCodeLine("mat4 MVP = " + t_projectionUniformName + " * " + t_viewUniformName  + " * "  + t_modelUniformName + ";");
        addVertexCodeLine("gl_Position = u_MVP * position;");
    }
}