cmake_minimum_required(VERSION 3.16.0)

project(DearImGui)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/imgui-master)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/imgui-master)

set(SOURCEFILES
    ${SOURCE_DIR}/imgui_draw.cpp
    ${SOURCE_DIR}/imgui_tables.cpp
    ${SOURCE_DIR}/imgui_widgets.cpp
    ${SOURCE_DIR}/imgui.cpp
)
set(INCLUDEFILES
    ${INCLUDE_DIR}/imconfig.h
    ${INCLUDE_DIR}/imgui.h
)

add_library(${PROJECT_NAME} STATIC
    ${SOURCEFILES}
    ${INCLUDEFILES}
)

target_include_directories(${PROJECT_NAME}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/imgui-master
)