add_library(Application OBJECT
    application.cpp
)

target_include_directories(Application PUBLIC
    ${CMAKE_SOURCE_DIR}/MyEngine/include/Application
)