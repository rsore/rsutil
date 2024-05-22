cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

project(rsutil)

add_library(rsutil STATIC
        include/rsutil/time.hpp
        src/time.cpp
        include/rsutil/fundamental.hpp
        include/rsutil/assert.hpp
)

target_include_directories(rsutil
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/include
)
