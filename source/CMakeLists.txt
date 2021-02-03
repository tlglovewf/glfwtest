message(STATUS "------Build Source Library---------")

file(GLOB_RECURSE CPPSOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp 
                             ${CMAKE_CURRENT_SOURCE_DIR}/render/*.cpp)

add_library(${MYSDK} ${CPPSOURCES})
target_link_libraries(${MYSDK} GL X11 -pthread -lm dl)