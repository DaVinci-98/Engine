option(BUILD_SHARED_LIBS OFF)
option(BUILD_TESTS OFF)
set(BUILD_STATIC_LIBS ON)

find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${CMAKE_SOURCE_DIR}/.git")
# Update submodules as needed
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()

#GLAD2
add_subdirectory(glad)

#SPDLOG
add_subdirectory(spdlog)

#STB
add_subdirectory(stb)

#TINYXML2
add_subdirectory(tinyxml2)

#GLM
add_subdirectory(glm)

#IMGUI
add_subdirectory(imgui)

#GLFW
add_subdirectory(glfw)