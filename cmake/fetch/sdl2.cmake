if(NOT Vulkan_FOUND)
    include(deps/vulkan.cmake)
endif()

FetchContent_GetProperties(sdl2)
if(NOT sdl2_POPULATED)
    FetchContent_Declare(
        sdl2
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG        8a5ba43d00252c6c8b33c9aa4f1048222955ab4d # 2.28.3
      )
  
    FetchContent_MakeAvailable(sdl2)
endif()
