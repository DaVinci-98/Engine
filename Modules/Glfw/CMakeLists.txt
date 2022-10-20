set(TARGET Glfw)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include/${TARGET})

set(SOURCEFILES
    ${SOURCE_DIR}/window.cpp
    ${SOURCE_DIR}/Events/keyEvent.cpp
    ${SOURCE_DIR}/Events/keyEventListener.cpp
    ${SOURCE_DIR}/Events/keyEventEmitter.cpp
    ${SOURCE_DIR}/Events/mouseKeyEvent.cpp
    ${SOURCE_DIR}/Events/mouseKeyEventListener.cpp
    ${SOURCE_DIR}/Events/mouseKeyEventEmitter.cpp
    ${SOURCE_DIR}/Events/mouseMoveEvent.cpp
    ${SOURCE_DIR}/Events/mouseMoveEventListener.cpp
    ${SOURCE_DIR}/Events/mouseMoveEventEmitter.cpp
    ${SOURCE_DIR}/Events/windowEvent.cpp
    ${SOURCE_DIR}/Events/windowEventListener.cpp
    ${SOURCE_DIR}/Events/windowEventEmitter.cpp
)
set(INCLUDEFILES
    ${INCLUDE_DIR}/window.hpp
    ${INCLUDE_DIR}/Events/keyEvent.hpp
    ${INCLUDE_DIR}/Events/keyEventListener.hpp
    ${INCLUDE_DIR}/Events/keyEventEmitter.hpp
    ${INCLUDE_DIR}/Events/mouseKeyEvent.hpp
    ${INCLUDE_DIR}/Events/mouseKeyEventListener.hpp
    ${INCLUDE_DIR}/Events/mouseKeyEventEmitter.hpp
    ${INCLUDE_DIR}/Events/mouseMoveEvent.hpp
    ${INCLUDE_DIR}/Events/mouseMoveEventListener.hpp
    ${INCLUDE_DIR}/Events/mouseMoveEventEmitter.hpp
    ${INCLUDE_DIR}/Events/windowEvent.hpp
    ${INCLUDE_DIR}/Events/windowEventListener.hpp
    ${INCLUDE_DIR}/Events/windowEventEmitter.hpp
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
    PUBLIC glfw
    PRIVATE glad
    PRIVATE Logger
)