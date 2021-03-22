include_directories(${CMAKE_SOURCE_DIR}/Vendor/glad/sources/include)

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