if(NOT Vulkan_FOUND)
    include(thirdparty/vulkan.cmake)
endif()

FetchContent_GetProperties(sdl2)
if(NOT sdl2_POPULATED)
    FetchContent_Declare(
        sdl2
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG        ac13ca9ab691e13e8eebe9684740ddcb0d716203 # 2.26.5
      )
  
    FetchContent_MakeAvailable(sdl2)
    #add_subdirectory(${glfw_SOURCE_DIR} ${glfw_BINARY_DIR})
endif()
