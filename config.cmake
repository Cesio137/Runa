add_subdirectory(thirdparty)
add_subdirectory(cmake)
add_subdirectory(data)
add_subdirectory(Source)

add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:Qt6::Core> $<TARGET_FILE:${CMAKE_PROJECT_NAME}>/../
)

