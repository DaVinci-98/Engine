set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(Physics OBJECT
    body2D.cpp
    physicsGroup.cpp
    physicsManager.cpp
    Events/collisionEvent.cpp
    Events/collisionEventEmitter.cpp
    Events/collisionEventListener.cpp
)