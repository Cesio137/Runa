set(ENGINE_DIR ${CMAKE_CURRENT_LIST})

file(GLOB engine_files "*.h" "*.cpp")
target_sources(${CMAKE_PROJECT_NAME} PUBLIC ${engine_files})
