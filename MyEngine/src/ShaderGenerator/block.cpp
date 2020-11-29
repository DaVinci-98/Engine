#include "ShaderGenerator/block.hpp"

namespace MyEngine::ShaderGenerator
{
    std::string Block::getTypeString(FieldType t_type)
    {
        switch (t_type)
        {
        case VEC2:
            return "vec2";
        case VEC3:
            return "vec3";
        case VEC4:
            return "vec4";
        case MAT4:
            return "mat4";
        case SAMPLER2D:
            return "sampler2D";
        default:
            return "";
        }
    }

    int Block::getTypeSize(FieldType t_type)
    {
        switch (t_type)
        {
        case VEC2:
            return 2;
        case VEC3:
            return 3;
        case VEC4:
            return 4;
        default:
            return -1;
        }
    }
}