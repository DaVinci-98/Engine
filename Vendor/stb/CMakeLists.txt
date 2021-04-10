cmake_minimum_required(VERSION 3.1)
project(stb CXX)

if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/stb-master/.git")
    message(WARNING "Stb submodule was not downloaded! GIT_SUBMODULE was turned off or failed.")
    message(STATUS "Checking if package was installed.")

    find_library(STB_FOUND stb)
    if(NOT STB_FOUND)
        message(FATAL_ERROR "Package not present, cannot continue.")
    endif()
else()
  set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
  set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/stb-master)

  set(SOURCEFILES
      ${SOURCE_DIR}/stbimage.cpp
  )

  set(INCLUDEFILES
      ${INCLUDE_DIR}/stb_image.h
  )

  add_library(${PROJECT_NAME} STATIC
      ${SOURCEFILES}
      ${INCLUDEFILES}
  )

  target_include_directories(${PROJECT_NAME}
      PUBLIC ${INCLUDE_DIR}
  )
endif()