if(NOT Vulkan_FOUND)
    include(deps/vulkan.cmake)
endif()

FetchContent_GetProperties(sdl2)
if(NOT sdl2_POPULATED)
    FetchContent_Declare(
        sdl2
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG        release-2.28.4 #2.28.4 
        GIT_PROGRESS TRUE
      )
  
    FetchContent_MakeAvailable(sdl2)
endif()

