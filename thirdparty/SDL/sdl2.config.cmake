set(SDL_DIR ${CMAKE_CURRENT_LIST_DIR})

add_subdirectory(${SDL_DIR}/SDL2)
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${SDL_DIR}/SDL2/include)

