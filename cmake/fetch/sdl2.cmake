if(NOT Vulkan_FOUND)
    include(deps/vulkan.cmake)
endif()

FetchContent_GetProperties(sdl2)
if(NOT sdl2_POPULATED)
    FetchContent_Declare(
        sdl2
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG        release-2.28.5 #2.28.5
        GIT_PROGRESS TRUE
      )
  
    FetchContent_MakeAvailable(sdl2)
    set_target_properties(SDL2  PROPERTIES FOLDER Thirdparty)
    set_target_properties(SDL2main PROPERTIES FOLDER Thirdparty)
    set_target_properties(sdl_headers_copy  PROPERTIES FOLDER Thirdparty)
    set_target_properties(uninstall PROPERTIES FOLDER Thirdparty)
endif()
