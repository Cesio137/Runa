add_subdirectory(doc)
add_subdirectory(thirdparty)
add_subdirectory(cmake)
add_subdirectory(source) 

add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:Qt6::Core> $<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>/
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>/assets
)

