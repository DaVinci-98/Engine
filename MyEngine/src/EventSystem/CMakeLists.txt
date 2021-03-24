set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(EventSystem OBJECT
    event.cpp
    eventEmitter.cpp
    eventListener.cpp)