
set(TARGET Physics)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include/${TARGET})

set(SOURCEFILES
    ${SOURCE_DIR}/body2D.cpp
    ${SOURCE_DIR}/physicsGroup.cpp
    ${SOURCE_DIR}/physicsManager.cpp
    ${SOURCE_DIR}/Events/collisionEvent.cpp
    ${SOURCE_DIR}/Events/collisionEventEmitter.cpp
    ${SOURCE_DIR}/Events/collisionEventListener.cpp
)
set(INCLUDEFILES
    ${INCLUDE_DIR}/body2D.hpp
    ${INCLUDE_DIR}/physicsGroup.hpp
    ${INCLUDE_DIR}/physicsManager.hpp
    ${INCLUDE_DIR}/Events/collisionEvent.hpp
    ${INCLUDE_DIR}/Events/collisionEventEmitter.hpp
    ${INCLUDE_DIR}/Events/collisionEventListener.hpp
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
    PUBLIC glm_static
    PRIVATE Helpers
)