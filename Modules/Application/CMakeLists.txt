set(TARGET Application)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include/${TARGET})

set(SOURCEFILES
    ${SOURCE_DIR}/application.cpp
)
set(INCLUDEFILES
    ${INCLUDE_DIR}/MyEngine.hpp
    ${INCLUDE_DIR}/entryPoint.hpp
    ${INCLUDE_DIR}/application.hpp
)

add_library(${TARGET} OBJECT
    ${SOURCEFILES}
    ${INCLUDEFILES}
)

target_include_directories(${TARGET}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(${TARGET}
    PUBLIC Glfw
    PUBLIC Renderer
    PUBLIC Physics
    PRIVATE Logger
    PRIVATE glad
)