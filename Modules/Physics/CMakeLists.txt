
set(TARGET Physics)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include/${TARGET})

set(SOURCEFILES
    ${SOURCE_DIR}/body2D.cpp
    ${SOURCE_DIR}/physicsGroup.cpp
    ${SOURCE_DIR}/physicsManager.cpp
)
set(INCLUDEFILES
    ${INCLUDE_DIR}/body2D.hpp
    ${INCLUDE_DIR}/physicsGroup.hpp
    ${INCLUDE_DIR}/physicsManager.hpp
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
    PRIVATE Logger
)