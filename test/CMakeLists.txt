message(STATUS "------Build Test Programs---------")

#Read All Test Files And Build Test Program
FILE(GLOB TEST_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
FOREACH(TEST_FILE ${TEST_FILES})
    STRING(REGEX REPLACE ".*/(.*)/(.*)/*.cpp" "\\2" TEST_NAME ${TEST_FILE})
    MESSAGE("BUILD TEST PROGRAM " ${TEST_NAME})
    add_executable(${TEST_NAME}
    ${CMAKE_CURRENT_SOURCE_DIR}/${TEST_NAME}.cpp)
if(WIN32)
    target_link_libraries(${TEST_NAME} ${MYSDK})
else()
    target_link_libraries(${TEST_NAME} ${MYSDK} GL X11 -pthread -lm dl)
endif()
ENDFOREACH()


  