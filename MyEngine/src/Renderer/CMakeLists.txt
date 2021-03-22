include_directories(${CMAKE_SOURCE_DIR}/Vendor/glad/sources/include)
include_directories(${CMAKE_SOURCE_DIR}/Vendor/tinyxml2)

add_library(Renderer OBJECT
    drawable2D.cpp
    mesh2D.cpp
    triangle2D.cpp
    triangle.cpp
    shader.cpp
    text.cpp
    renderer.cpp
    material.cpp
    Events/drawableAddEvent.cpp
    Events/drawableAddEventEmitter.cpp
    Events/drawableAddEventListener.cpp
)