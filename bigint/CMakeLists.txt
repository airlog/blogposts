cmake_minimum_required (VERSION 2.6)
project (bigint)

if (NOT CMAKE_BUILD_TYPE)
	message(STATUS "No build type selected, default to RELEASE")
	set(CMAKE_BUILD_TYPE "release")
endif()

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -O2")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set (PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set (PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# The version number.
set(VERSION_MAJOR 1)
set(VERSION_MINOR 0)
set(VERSION_PATCH 0)
set(VERSION_STRING ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH})

set(PROJECT_SOURCES
    ${PROJECT_SOURCE_DIR}/bigint.c
    ${PROJECT_SOURCE_DIR}/consts.c
    ${PROJECT_SOURCE_DIR}/add.c
    ${PROJECT_SOURCE_DIR}/multiply.c
    ${PROJECT_SOURCE_DIR}/hexstring.c
)

include_directories("${PROJECT_BINARY_DIR}")
include_directories("${PROJECT_INCLUDE_DIR}")

add_library(bigint SHARED ${PROJECT_SOURCES})

set_target_properties(bigint PROPERTIES VERSION ${VERSION_STRING} SOVERSION ${VERSION_MAJOR})

