cmake_minimum_required(VERSION 3.16.0)

project(Engine)

set(CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# option(BUILD_SANDBOX "Build sandbox executable" OFF)

add_subdirectory(Vendor)
add_subdirectory(MyEngine)

# if(BUILD_SANDBOX)
#     add_subdirectory(Sandbox)
# endif