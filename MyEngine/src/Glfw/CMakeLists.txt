include_directories(${CMAKE_SOURCE_DIR}/Vendor/glad/sources/include)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(Glfw OBJECT
    window.cpp
    Events/keyEvent.cpp
    Events/keyEventListener.cpp
    Events/keyEventEmitter.cpp
    Events/mouseKeyEvent.cpp
    Events/mouseKeyEventListener.cpp
    Events/mouseKeyEventEmitter.cpp
    Events/mouseMoveEvent.cpp
    Events/mouseMoveEventListener.cpp
    Events/mouseMoveEventEmitter.cpp
    Events/windowEvent.cpp
    Events/windowEventListener.cpp
    Events/windowEventEmitter.cpp
)