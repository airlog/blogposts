cmake_minimum_required (VERSION 2.6)
project (bigint-example-factorial)

if (NOT CMAKE_BUILD_TYPE)
	message(STATUS "No build type selected, default to RELEASE")
	set(CMAKE_BUILD_TYPE "release")
endif()

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

set (BIGINT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/../../include/)
set (BIGINT_LIBRARY_DIR ${PROJECT_SOURCE_DIR}/../../lib/)

set (PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/)

set(PROJECT_SOURCES
    ${PROJECT_SOURCE_DIR}/factorial.c
)

include_directories("${PROJECT_BINARY_DIR}")
include_directories("${BIGINT_INCLUDE_DIR}")

link_directories(${BIGINT_LIBRARY_DIR})

add_executable(factorial ${PROJECT_SOURCES})
target_link_libraries(factorial bigint)

