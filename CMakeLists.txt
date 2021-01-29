cmake_minimum_required(VERSION 3.0)

project(GLFWTest)

set(CMAKE_LEGACY_CYGWIN_WIN32 OFF)

if (POLICY CMP0054)
    cmake_policy(SET CMP0054 NEW)
endif()

if (POLICY CMP0077)
    cmake_policy(SET CMP0077 NEW)
endif()

link_libraries(glfw3 glad)

add_definitions(-std=c++14)

add_executable(${PROJECT_NAME} test_glfw.cpp)

target_link_libraries(${PROJECT_NAME} GL X11 -pthread -lm dl)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB FILES "${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp")


set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/output")

message(${FILES})

add_executable("test" test_cpp.cpp ${FILES})