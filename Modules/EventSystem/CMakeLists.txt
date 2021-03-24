set(TARGET EventSystem)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include/${TARGET})

set(SOURCEFILES
    ${SOURCE_DIR}/event.cpp
    ${SOURCE_DIR}/eventEmitter.cpp
    ${SOURCE_DIR}/eventListener.cpp
)
set(INCLUDEFILES
    ${INCLUDE_DIR}/event.hpp
    ${INCLUDE_DIR}/eventEmitter.hpp
    ${INCLUDE_DIR}/eventListener.hpp
)

add_library(${TARGET} OBJECT
    ${SOURCEFILES}
    ${INCLUDEFILES}
)

target_include_directories(${TARGET}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)