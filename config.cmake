set_target_properties(Nanometro PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/Nanometro
)



set(RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/Nanometro)

add_subdirectory(Engine)

add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
        #COMMAND  ${CMAKE_COMMAND} -E copy ${SDL2_SHARE_LIBRARY} $<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>

        #Source
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/Engine/Misc $<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>/Engine/Misc
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/Engine/Source $<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>/Engine/Source

        #Game
        #COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/Game/Content $<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>/Game/Content
)
