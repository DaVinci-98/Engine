include_directories(${CMAKE_SOURCE_DIR}/Vendor/spdlog/include)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(Helpers OBJECT
    logger.cpp
)