set(MAIN_DIR  ${CMAKE_CURRENT_LIST_DIR}/../)

project(Example C)

set(Example_LIBRARIES -L${CMAKE_CURRENT_BINARY_DIR}/lib/ -lasound SAM_Sound)
set(Example_SOURCES ${MAIN_DIR}/Example/main.c)

include_directories(${MAIN_DIR}/include)

add_executable(Example ${Example_SOURCES})

target_link_libraries(Example ${Example_LIBRARIES})
set_target_properties(Example PROPERTIES OUTPUT_NAME "samsound_example")