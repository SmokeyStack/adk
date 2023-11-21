cmake_minimum_required(VERSION 3.12)
cmake_policy(SET CMP0048 NEW)
cmake_policy(SET CMP0074 NEW)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(PROJECT_NAME adk-test)
project(${PROJECT_NAME} VERSION 0.1)

configure_file(
    CMakeLists.txt.in
    googletest-download/CMakeLists.txt
)
execute_process(
    COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download
)
execute_process(
    COMMAND ${CMAKE_COMMAND} --build .
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_subdirectory(
    ${CMAKE_BINARY_DIR}/googletest-src
    ${CMAKE_BINARY_DIR}/googletest-build
)

if (CMAKE_VERSION VERSION_LESS 2.8.11)
    include_directories("${gtest_SOURCE_DIR}/include"
            "${gmock_SOURCE_DIR}/include")
endif()

enable_testing()
add_subdirectory(test)

set(SOURCE_FILES Main.cpp)
add_library(${PROJECT_NAME} ${SOURCE_FILES})

# add_executable(manifest
#     Manifest.cpp
# )

# set(YAML_CPP_BUILD_TESTS OFF CACHE BOOL "disable yaml tests")
# set(YAML_CPP_BUILD_TOOLS OFF CACHE BOOL "disable yaml tools")
# set(YAML_CPP_BUILD_CONTRIB OFF CACHE BOOL "disable yaml contrib")

# add_subdirectory(yaml)
# target_link_libraries(manifest
#     yaml-cpp
# )