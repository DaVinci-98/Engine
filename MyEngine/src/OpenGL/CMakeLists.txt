include_directories(${CMAKE_SOURCE_DIR}/Vendor/glad/sources/include)
include_directories(${CMAKE_SOURCE_DIR}/Vendor/stb/include)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(OpenGL OBJECT
    glException.cpp
    indexBuffer.cpp
    shader.cpp
    texture.cpp
    vertexArray.cpp
    vertexBuffer.cpp
    vertexBufferLayout.cpp
)