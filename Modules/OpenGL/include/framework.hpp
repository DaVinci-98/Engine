# pragma once

#include "colour.hpp"
#include "texture.hpp"
#include "shader.hpp"

namespace MyEngine::OpenGL
{
    class Framework
    {
    public:
        static void initialize(); 
        static void close();
    };
}