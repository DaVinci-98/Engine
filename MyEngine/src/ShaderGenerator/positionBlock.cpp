#include "ShaderGenerator/positionBlock.hpp"

namespace MyEngine::ShaderGenerator
{
    PositionBlock::PositionBlock()
    {
        addVertexLocation("position", FieldType::VEC4);
        addVertexUniform("u_MVP", FieldType::MAT4);
        addVertexCodeLine("gl_Position = u_MVP * position;");
    }
}