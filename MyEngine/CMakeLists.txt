include_directories(${CMAKE_SOURCE_DIR}/MyEngine/include)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_subdirectory(src/Helpers)
add_subdirectory(src/Application)
add_subdirectory(src/EventSystem)
add_subdirectory(src/Glfw)
add_subdirectory(src/OpenGL)
add_subdirectory(src/Physics)
add_subdirectory(src/Renderer)
add_subdirectory(src/ShaderGenerator)

add_library(MyEngine SHARED
    $<TARGET_OBJECTS:Helpers>
    $<TARGET_OBJECTS:Application>
    $<TARGET_OBJECTS:EventSystem>
    $<TARGET_OBJECTS:Glfw>
    $<TARGET_OBJECTS:OpenGL>
    $<TARGET_OBJECTS:Physics>
    $<TARGET_OBJECTS:Renderer>
    $<TARGET_OBJECTS:ShaderGenerator>
)