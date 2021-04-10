cmake_minimum_required(VERSION 3.16.0)
project(DearImGui)

if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/imgui-master/.git")
    message(WARNING "Dear ImGui submodule was not downloaded! GIT_SUBMODULE was turned off or failed.")
    message(STATUS "Checking if package was installed.")

    find_library(IMGUI_FOUND imgui)
    if(NOT IMGUI_FOUND)
        message(FATAL_ERROR "Package not present, cannot continue.")
    endif()
else()
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
        PUBLIC ${INCLUDE_DIR}
    )
endif()