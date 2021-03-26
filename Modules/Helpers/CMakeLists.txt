
set(TARGET Helpers)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include/${TARGET})

set(SOURCEFILES
    ${SOURCE_DIR}/logger.cpp
)
set(INCLUDEFILES
    ${INCLUDE_DIR}/logger.hpp
    ${INCLUDE_DIR}/smartVector.hpp
    ${INCLUDE_DIR}/type.hpp
    ${INCLUDE_DIR}/zip.hpp
)

add_library(${TARGET} OBJECT
    ${SOURCEFILES}
    ${INCLUDEFILES}
)

target_include_directories(${TARGET}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(${TARGET}
    PUBLIC spdlog
)