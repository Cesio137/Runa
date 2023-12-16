add_subdirectory(CMake)
add_subdirectory(Engine)

add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:SDL2> $<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>/
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/Engine/Misc $<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>/Misc
)