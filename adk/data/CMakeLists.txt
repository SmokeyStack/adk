cmake_minimum_required(VERSION 3.12)
cmake_policy(SET CMP0048 NEW)
cmake_policy(SET CMP0074 NEW)

set(CMAKE_DISABLE_SOURCE_CHANGES ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
if("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
    message(FATAL_ERROR "In-source builds not allowed. Please run CMake from the './adk-build' directory. You may need to remove CMakeCache.txt.")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
option(GITHUB_ACTION "Are you running on GitHub Actions?" OFF)

set(BIN_NAME adk)
set(LIB_NAME adk-lib)

project(${BIN_NAME} VERSION 0.1)

file(GLOB_RECURSE SRC_FILES src/*.cpp )
file(GLOB_RECURSE HEADER_FILES include/*.h include/*.hpp)
add_library(${LIB_NAME} STATIC ${SRC_FILES})
file(COPY assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
if(GITHUB_ACTION)
	add_subdirectory(third-party/spdlog)
else()
	find_package(spdlog REQUIRED)
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

target_include_directories(${LIB_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_include_directories(${LIB_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
if(GITHUB_ACTION)
	target_link_libraries(${LIB_NAME} spdlog)
else()
	target_link_libraries(${LIB_NAME} PRIVATE spdlog::spdlog)
endif()


add_executable(${BIN_NAME} src/Main.cpp)
target_link_libraries(${BIN_NAME} PRIVATE ${LIB_NAME})
target_include_directories(${BIN_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})