set(target_name stringCOW_test)

add_executable(${target_name} src/stringCOWtest.cpp)

target_link_libraries(${target_name} PRIVATE
                        stringCOW
                        GTest::gtest_main)   

gtest_discover_tests(${target_name})