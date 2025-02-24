FetchContent_Declare(
        BOX2D
        URL https://github.com/erincatto/box2d/archive/refs/tags/v3.0.0.tar.gz
)

if (NOT BOX2D_POPULATED)
    set(CMAKE_POSITION_INDEPENDENT_CODE ON)
    set(GLFW_BUILD_WIN32 OFF CACHE INTERNAL "")
    set(BOX2D_SAMPLES OFF CACHE INTERNAL "")
    set(ENKITS_BUILD_C_INTERFACE OFF CACHE INTERNAL "")
    set(BOX2D_UNIT_TESTS OFF CACHE INTERNAL "")
endif ()

FetchContent_MakeAvailable(BOX2D)

set_target_properties(box2d PROPERTIES FOLDER "/engine/thirdparty/box2d")
set_target_properties(simde PROPERTIES FOLDER "/engine/thirdparty/box2d")