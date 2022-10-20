set(TARGET OpenGL)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include/${TARGET})

set(SOURCEFILES
    ${SOURCE_DIR}/glException.cpp
    ${SOURCE_DIR}/indexBuffer.cpp
    ${SOURCE_DIR}/shader.cpp
    ${SOURCE_DIR}/texture.cpp
    ${SOURCE_DIR}/vertexArray.cpp
    ${SOURCE_DIR}/vertexBuffer.cpp
    ${SOURCE_DIR}/vertexBufferLayout.cpp
)
set(INCLUDEFILES
    ${INCLUDE_DIR}/glException.hpp
    ${INCLUDE_DIR}/indexBuffer.hpp
    ${INCLUDE_DIR}/shader.hpp
    ${INCLUDE_DIR}/texture.hpp
    ${INCLUDE_DIR}/vertexArray.hpp
    ${INCLUDE_DIR}/vertexBuffer.hpp
    ${INCLUDE_DIR}/vertexBufferLayout.hpp
)

add_library(${TARGET} OBJECT
    ${SOURCEFILES}
    ${INCLUDEFILES}
)

target_include_directories(${TARGET}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(${TARGET}
    PUBLIC glm_static
    PRIVATE glad
    PRIVATE stb
    PRIVATE Logger
)