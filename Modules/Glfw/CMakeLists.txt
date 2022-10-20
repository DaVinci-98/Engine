set(TARGET Glfw)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include/${TARGET})

set(SOURCEFILES
    ${SOURCE_DIR}/window.cpp
)
set(INCLUDEFILES
    ${INCLUDE_DIR}/window.hpp
    ${INCLUDE_DIR}/Events/keyEvent.hpp
    ${INCLUDE_DIR}/Events/mouseKeyEvent.hpp
    ${INCLUDE_DIR}/Events/mouseMoveEvent.hpp
    ${INCLUDE_DIR}/Events/windowEvent.hpp
)

add_library(${TARGET} OBJECT
    ${SOURCEFILES}
    ${INCLUDEFILES}
)

target_include_directories(${TARGET}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(${TARGET}
    PUBLIC glfw
    PRIVATE glad
    PRIVATE Logger
)