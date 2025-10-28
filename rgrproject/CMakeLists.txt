cmake_minimum_required(VERSION 3.22)
project(stringCOW)

include(cmake/CompileOptions.cmake)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

enable_testing()

add_subdirectory(external)
add_subdirectory(src)
add_subdirectory(tests)