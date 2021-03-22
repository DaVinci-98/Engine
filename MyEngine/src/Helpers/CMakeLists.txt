include_directories(${CMAKE_SOURCE_DIR}/Vendor/spdlog/include)

add_library(Helpers OBJECT
    logger.cpp
)