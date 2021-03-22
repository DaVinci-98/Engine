include_directories(${CMAKE_SOURCE_DIR}/include)

add_library(ShaderGenerator OBJECT
    block.cpp
    colourBlock.cpp
    positionBlock.cpp
    shaderGen.cpp
    textureBlock.cpp
)