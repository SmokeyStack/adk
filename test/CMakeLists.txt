cmake_minimum_required(VERSION 3.12)
cmake_policy(SET CMP0048 NEW)
cmake_policy(SET CMP0074 NEW)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories("${PROJECT_SOURCE_DIR}/adk/data/include")
file(GLOB_RECURSE HEADER_FILES ${PROJECT_SOURCE_DIR}/adk/data/include/*.h ${PROJECT_SOURCE_DIR}/adk/data/include/*.hpp)
file(COPY ${PROJECT_SOURCE_DIR}/adk/data/assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${PROJECT_SOURCE_DIR}/test/files DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
find_package(spdlog REQUIRED)

add_executable(main AdkTest.cpp)
target_link_libraries(main gtest)

add_executable(BlockTest BlockTest.cpp ${PROJECT_SOURCE_DIR}/adk/data/src/registry_global.cpp ${PROJECT_SOURCE_DIR}/adk/data/src/utility/logger.cpp ${HEADER_FILES})
target_link_libraries(BlockTest PRIVATE gtest gmock_main spdlog::spdlog)
add_test(NAME BlockTest COMMAND BlockTest)

#add_test(
#    NAME BlockTest
#    COMMAND BlockTest
#)

#add_executable(ItemTest
#    ItemTest.cpp
#    GlobalRegistry.cpp
#    ${Headers})
#target_link_libraries(ItemTest PUBLIC
#    gtest_main
#    adkhead
#)

#add_test(
#    NAME ItemTest
#    COMMAND ItemTest
#)