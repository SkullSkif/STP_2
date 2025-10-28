set(target_name stringCOW)

add_library(${target_name} include/stringCOW/stringCOW.cpp)

target_include_directories(${target_name} PUBLIC include)

set_compile_options(${target_name})