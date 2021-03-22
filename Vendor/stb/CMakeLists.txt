cmake_minimum_required(VERSION 3.1)
project(stb CXX)

add_library(stb STATIC
    src/stbimage.cpp
)

target_include_directories(stb PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/>
  $<INSTALL_INTERFACE:include/> 
)