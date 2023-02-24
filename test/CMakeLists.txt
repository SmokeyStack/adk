cmake_minimum_required(VERSION 3.12)

set(This BlockTests)

set(Sources
    BlockTest.cpp
)

add_executable(${This} ${Sources})
target_link_libraries(${This} PUBLIC
    gtest_main
    adkhead
)

add_test(
    NAME ${This}
    COMMAND ${This}
)