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
        include/rsutil/scientific.hpp
        include/rsutil/format.hpp
        src/format.cpp
        include/rsutil/math.hpp
        include/rsutil/file_system.hpp
)

target_include_directories(rsutil PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/include
)

option(RSUTIL_ENABLE_DYNAMIC_ASSERTS "Enable dynamic asserts" ON)
message(STATUS "RSUTIL_ENABLE_DYNAMIC_ASSERTS is ${RSUTIL_ENABLE_DYNAMIC_ASSERTS}")

target_compile_definitions(rsutil PUBLIC
        $<$<BOOL:${RSUTIL_ENABLE_DYNAMIC_ASSERTS}>:RSUTIL_ENABLE_DYNAMIC_ASSERT=1>
        $<$<NOT:$<BOOL:${RSUTIL_ENABLE_DYNAMIC_ASSERTS}>>:RSUTIL_ENABLE_DYNAMIC_ASSERT=0>
)