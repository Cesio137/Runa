FetchContent_GetProperties(bgfx)
if(NOT bgfx_POPULATED)
    FetchContent_Declare(
            bgfx
            GIT_REPOSITORY https://github.com/bkaradzic/bgfx.cmake.git
            GIT_TAG        a6cfe968a52e556720f47a2b0032fbb26d8ab7f9 # 1.118.8415-411
    )

    FetchContent_MakeAvailable(bgfx)
endif()