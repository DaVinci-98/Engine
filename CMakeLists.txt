cmake_minimum_required(VERSION 3.16.0)

project(MyEngine)

set(LIBRARY_NAME ${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(VENDOR_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Vendor")
set(MODULES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Modules")

add_subdirectory(${VENDOR_DIR})
add_subdirectory(${MODULES_DIR})

add_library(${LIBRARY_NAME} SHARED
    $<TARGET_OBJECTS:Logger>
    $<TARGET_OBJECTS:Application>
    $<TARGET_OBJECTS:EventSystem>
    $<TARGET_OBJECTS:Glfw>
    $<TARGET_OBJECTS:OpenGL>
    $<TARGET_OBJECTS:Physics>
    $<TARGET_OBJECTS:Renderer>
)

target_link_libraries(${LIBRARY_NAME}
    PUBLIC Application
)