include_directories(${CMAKE_SOURCE_DIR}/include)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(ShaderGenerator OBJECT
    block.cpp
    colourBlock.cpp
    positionBlock.cpp
    shaderGen.cpp
    textureBlock.cpp
)