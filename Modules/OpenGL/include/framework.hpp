# pragma once

#include "colour.hpp"
#include "texture.hpp"
#include "shader.hpp"

namespace MyEngine
{
    class Framework
    {
    public:
        void initialize(); 
        void updateVertexArray();
        unsigned int loadTexture(std::string& path);

    };
}