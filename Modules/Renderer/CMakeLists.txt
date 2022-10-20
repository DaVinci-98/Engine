set(TARGET Renderer)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include/${TARGET})

set(SOURCEFILES
    ${SOURCE_DIR}/drawable2D.cpp
    ${SOURCE_DIR}/mesh2D.cpp
    ${SOURCE_DIR}/triangle2D.cpp
    ${SOURCE_DIR}/triangle.cpp
    ${SOURCE_DIR}/shader.cpp
    ${SOURCE_DIR}/text.cpp
    ${SOURCE_DIR}/renderer.cpp
    ${SOURCE_DIR}/material.cpp
)
set(INCLUDEFILES
    ${INCLUDE_DIR}/drawable2D.hpp
    ${INCLUDE_DIR}/mesh2D.hpp
    ${INCLUDE_DIR}/triangle2D.hpp
    ${INCLUDE_DIR}/triangle.hpp
    ${INCLUDE_DIR}/shader.hpp
    ${INCLUDE_DIR}/text.hpp
    ${INCLUDE_DIR}/renderer.hpp
    ${INCLUDE_DIR}/material.hpp
)

add_library(${TARGET} OBJECT
    ${SOURCEFILES}
    ${INCLUDEFILES}
)

target_include_directories(${TARGET}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(${TARGET}
    PUBLIC EventSystem
    PUBLIC OpenGL
    PRIVATE glad
    PRIVATE tinyxml2
    PRIVATE Logger
)