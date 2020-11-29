#include "ShaderGenerator/colourBlock.hpp"

namespace MyEngine::ShaderGenerator
{
    ColourBlock::ColourBlock()
    {
        addVertexLocation("vertexColour", FieldType::VEC4);
        addVertexOut("v_colour", FieldType::VEC4);
        addVertexCodeLine("v_colour = vertexColour;");

        addFragmentLocation("color", FieldType::VEC4);
        addFragmentIn("v_colour", FieldType::VEC4);
        addFragmentCodeLine("color = v_colour");
    }
}