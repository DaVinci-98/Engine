cmake_minimum_required(VERSION 3.16.0)

project(Modules)

add_subdirectory(${MODULES_DIR}/Logger)
add_subdirectory(${MODULES_DIR}/Application)
add_subdirectory(${MODULES_DIR}/Glfw)
add_subdirectory(${MODULES_DIR}/OpenGL)
add_subdirectory(${MODULES_DIR}/Physics)
add_subdirectory(${MODULES_DIR}/Renderer)
