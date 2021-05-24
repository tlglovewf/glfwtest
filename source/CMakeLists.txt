message(STATUS "------Build Source Library---------")

file(GLOB_RECURSE CPPSOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp 
                             ${CMAKE_CURRENT_SOURCE_DIR}/render/*.cpp)
FILE(GLOB TESS_FILES "${CMAKE_CURRENT_SOURCE_DIR}/geometry/tess/*.c")
if(WIN32)
   LIST(APPEND CPPSOURCES ${CMAKE_CURRENT_SOURCE_DIR}/glad.c)
endif()
add_library(${MYSDK} ${CPPSOURCES} ${TESS_FILES})

if(WIN32)
   target_link_libraries(${MYSDK} "E:/Sources/glfw-3.3.4/lib/glfw3.lib")
else()
    target_link_libraries(${MYSDK} GL X11 -pthread -lm dl) 
endif()