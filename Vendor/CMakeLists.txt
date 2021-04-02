option(BUILD_SHARED_LIBS OFF)
option(BUILD_TESTS OFF)
set(BUILD_STATIC_LIBS ON)

#GLAD2
add_subdirectory(glad)

#SPDLOG
add_subdirectory(spdlog)

#STB
add_subdirectory(stb)

#TINYXML2
add_subdirectory(tinyxml2)

#GLM
add_subdirectory(glm-master)

#IMGUI
add_subdirectory(imgui)