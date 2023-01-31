file(GLOB_RECURSE Engine_Sources "*.h" "*.cpp")
target_sources(${CMAKE_PROJECT_NAME} PUBLIC ${Engine_Sources})
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR})