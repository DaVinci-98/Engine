#include "ShaderGenerator/textureBlock.hpp"

namespace MyEngine::ShaderGenerator
{
    TextureBlock::TextureBlock(std::string t_textureUniformName)
    {
        addVertexLocation("texCoord", FieldType::VEC2);
        addVertexOut("v_texCoord", FieldType::VEC2);
        addVertexCodeLine("v_texCoord = texCoord;");

        addFragmentLocation("color", FieldType::VEC4);
        addFragmentUniform(t_textureUniformName, FieldType::SAMPLER2D);
        addFragmentIn("v_texCoord", FieldType::VEC2);
        addFragmentCodeLine("color = texture(" + t_textureUniformName + ", v_texCoord);");
    }
}