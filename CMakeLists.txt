cmake_minimum_required(VERSION 3.16.0)

project(Engine)

option(BUILD_SANDBOX "Build sandbox executable" OFF)

add_subdirectory(Vendor)
add_subdirectory(MyEngine)

if(BUILD_SANDBOX)
    add_subdirectory(Sandbox)
endif()