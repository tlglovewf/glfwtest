cmake_minimum_required(VERSION 3.0)

project(GLFWTest)

set(CMAKE_LEGACY_CYGWIN_WIN32 OFF)

if (POLICY CMP0054)
    cmake_policy(SET CMP0054 NEW)
endif()

if (POLICY CMP0077)
    cmake_policy(SET CMP0077 NEW)
endif()

option(BUILD_TEST "build test program" ON)

# add_definitions(-std=c++11)

list(APPEND CMAKE_CXX_FLAGS "-std=c++11")
 
if("${CMAKE_BUILD_TYPE}" STREQUAL "")
    set(CMAKE_BUILD_TYPE "Debug")
endif()

message("Build Type : " ${CMAKE_BUILD_TYPE})

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/output")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

link_libraries(glfw3 glad)

set(MYSDK "mygl")

add_definitions(-DSHADERS_PATH="${PROJECT_SOURCE_DIR}/shaders/")

add_subdirectory(source)


if(BUILD_TEST)
    add_subdirectory(test)
endif()
