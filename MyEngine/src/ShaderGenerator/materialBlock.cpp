#include "ShaderGenerator/materialBlock.hpp"

namespace MyEngine::ShaderGenerator
{
    MaterialBlock::MaterialBlock(MaterialType t_type)
    {
        switch(t_type)
        {
        case TEXTURE:
            addVertexLocation("texCoord", FieldType::VEC2);
            addVertexOut("v_texCoord", FieldType::VEC2);
            addVertexCodeLine("v_texCoord = texCoord;");

            addFragmentLocation("color", FieldType::VEC4);
            addFragmentUniform("u_texture", FieldType::SAMPLER2D);
            addFragmentIn("v_texCoord", FieldType::VEC2);
            addFragmentCodeLine("color = texture(u_texture, v_texCoord);");
            break;
        case COLOUR:
            addVertexLocation("vertexColour", FieldType::VEC4);
            addVertexOut("v_colour", FieldType::VEC4);
            addVertexCodeLine("v_colour = vertexColour;");

            addFragmentLocation("color", FieldType::VEC4);
            addFragmentIn("v_colour", FieldType::VEC4);
            addFragmentCodeLine("color = v_colour");
            break;
        }
    }
}