#GLAD2

cmake_minimum_required(VERSION 3.1)
project(glad)

set(GLAD_SOURCES_DIR "${PROJECT_SOURCE_DIR}/glad-glad2/")
add_subdirectory("${GLAD_SOURCES_DIR}cmake" glad_cmake)
glad_add_library(glad STATIC REPRODUCIBLE API gl:core=4.5 LOCATION ${PROJECT_SOURCE_DIR}/sources)