if(NOT Vulkan_FOUND)
    include(deps/vulkan.cmake)
endif()

FetchContent_GetProperties(sdl2)
if(NOT sdl2_POPULATED)
    FetchContent_Declare(
        sdl2
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG        cc016b0046d563287f0aa9f09b958b5e70d43696 #2.28.4 
      )
  
    FetchContent_MakeAvailable(sdl2)
endif()

