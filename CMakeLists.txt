cmake_minimum_required(VERSION 3.21)
project(SAM_Sound C)

set(CMAKE_C_STANDARD 99)
set(PROJECT_NAME SAM-Sound)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/lib)

set(LIBRARIES -lasound)

set(SOURCES
        source/samsound.c include/samsound.h

        include/pcm.h source/pcm.c
        )

include_directories(include)

add_library(SAM_Sound SHARED ${SOURCES})

target_link_libraries(SAM_Sound ${LIBRARIES})

set_target_properties(SAM_Sound PROPERTIES OUTPUT_NAME "samsound")

include(cmake/Example.cmake)