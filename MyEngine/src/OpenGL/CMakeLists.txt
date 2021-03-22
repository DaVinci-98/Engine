include_directories(${CMAKE_SOURCE_DIR}/Vendor/glad/sources/include)
include_directories(${CMAKE_SOURCE_DIR}/Vendor/stb/include)

add_library(OpenGL OBJECT
    glException.cpp
    indexBuffer.cpp
    shader.cpp
    texture.cpp
    vertexArray.cpp
    vertexBuffer.cpp
    vertexBufferLayout.cpp
)