cmake_minimum_required(VERSION 3.16.0)

project(Sandbox)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

set(SOURCEFILES
    ${SOURCE_DIR}/ball.cpp
    ${SOURCE_DIR}/breakableBlock.cpp
    ${SOURCE_DIR}/platform.cpp
    ${SOURCE_DIR}/sandbox.cpp
)
set(INCLUDEFILES
    ${INCLUDE_DIR}/ball.hpp
    ${INCLUDE_DIR}/breakableBlock.hpp
    ${INCLUDE_DIR}/platform.hpp
    ${INCLUDE_DIR}/sandbox.hpp
)

add_executable(${PROJECT_NAME}
    ${SOURCEFILES}
    ${INCLUDEFILES}
)

target_include_directories(${PROJECT_NAME}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE MyEngine
)