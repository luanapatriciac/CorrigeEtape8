
add_executable(mainLauncher mainLauncher.cpp)

target_link_libraries(mainLauncher PUBLIC src pugixml sfml-graphics)

add_custom_target(copy-resources ALL DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/visage.xml)
add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/visage.xml
                   DEPENDS ${CMAKE_SOURCE_DIR}/resources/visage.xml
                   COMMAND ${CMAKE_COMMAND} -E copy
                           ${CMAKE_SOURCE_DIR}/resources/visage.xml
                           ${CMAKE_CURRENT_BINARY_DIR})
