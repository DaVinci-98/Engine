# pragma once

#include "OpenGL/colour.hpp"
#include "OpenGL/texture.hpp"
#include "OpenGL/shader.hpp"

namespace MyEngine::OpenGL
{
    class Framework
    {
    public:
        static void initialize(); 
        static void close();
    };
}