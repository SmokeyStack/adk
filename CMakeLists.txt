cmake_minimum_required(VERSION 3.12)

set(This adkhead)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

project(${This} C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE)

enable_testing()

add_subdirectory(googletest)

set(Headers
    Main.h
)

set(Sources
    Main.cpp
)

add_library(${This} STATIC ${Sources} ${Headers})

add_subdirectory(test)

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