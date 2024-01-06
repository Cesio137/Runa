add_subdirectory(CMake)
add_subdirectory(Engine)


add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
        #COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:SDL2> $<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>/
        #COMMAND  ${CMAKE_COMMAND} -E copy ${SDL2_DIR}/bin/SDL2.dll $<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>
        #COMMAND  ${CMAKE_COMMAND} -E copy ${ZLIB_DIR}/bin/zlib.dll $<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>

        #Source
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/Engine/Misc $<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>/Engine/Misc
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/Engine/Source $<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>/Engine/Source
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/Engine/Plugins $<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>/Engine/Plugins

        #Game
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/Game/Content $<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>/Game/Content
)