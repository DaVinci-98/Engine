
set(TARGET ShaderGenerator)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include/${TARGET})

set(SOURCEFILES
    ${SOURCE_DIR}/block.cpp
    ${SOURCE_DIR}/colourBlock.cpp
    ${SOURCE_DIR}/positionBlock.cpp
    ${SOURCE_DIR}/shaderGen.cpp
    ${SOURCE_DIR}/textureBlock.cpp
)
set(INCLUDEFILES
    ${INCLUDE_DIR}/block.hpp
    ${INCLUDE_DIR}/colourBlock.hpp
    ${INCLUDE_DIR}/positionBlock.hpp
    ${INCLUDE_DIR}/shaderGen.hpp
    ${INCLUDE_DIR}/textureBlock.hpp
)

add_library(${TARGET} OBJECT
    ${SOURCEFILES}
    ${INCLUDEFILES}
)

target_include_directories(${TARGET}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(${TARGET}
    PUBLIC glm_static)