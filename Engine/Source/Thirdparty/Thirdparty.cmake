set(THIRDPARTY_DIR ${CMAKE_CURRENT_LIST_DIR})

add_subdirectory(${THIRDPARTY_DIR}/GLAD)
add_subdirectory(${THIRDPARTY_DIR}/libpng)
add_subdirectory(${THIRDPARTY_DIR}/zlib)
add_subdirectory(${THIRDPARTY_DIR}/SDL2)
add_subdirectory(${THIRDPARTY_DIR}/SDL_image)
#add_subdirectory(${THIRDPARTY_DIR}/luajit)
add_subdirectory(${THIRDPARTY_DIR}/lua)
add_subdirectory(${THIRDPARTY_DIR}/imgui)
add_subdirectory(${THIRDPARTY_DIR}/nlohmann)

set_target_properties(imgui PROPERTIES FOLDER "Engine/Source/Thirdparty")