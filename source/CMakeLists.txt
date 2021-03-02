message(STATUS "------Build Source Library---------")

file(GLOB_RECURSE CPPSOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp 
                             ${CMAKE_CURRENT_SOURCE_DIR}/render/*.cpp)
FILE(GLOB TESS_FILES "${CMAKE_CURRENT_SOURCE_DIR}/geometry/tess/*.c")
add_library(${MYSDK} ${CPPSOURCES} ${TESS_FILES})
target_link_libraries(${MYSDK} GL X11 -pthread -lm dl) 