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

    get_all_targets(sdl2_targets)
    message("All targets: ${sdl2_targets}")

    set_property(GLOBAL PROPERTY USE_FOLDERS ON)
    set_target_properties(${sdl2_targets} PROPERTIES FOLDER Thirdparty)
endif()
