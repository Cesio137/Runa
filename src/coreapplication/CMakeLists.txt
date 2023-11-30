set(CoreApplication_DIR ${CMAKE_CURRENT_LIST_DIR})

project(CoreApplication)
file(GLOB_RECURSE CoreApplication_Sources "${CoreApplication_DIR}/public/*.h" "${CoreApplication_DIR}/private/*.h" "${CoreApplication_DIR}/public/*.cpp" "${CoreApplication_DIR}/private/*.cpp")
add_library(CoreApplication STATIC ${CoreApplication_Sources})
target_include_directories(CoreApplication
        PUBLIC
        "${CoreApplication_DIR}/public"
)
target_link_libraries(CoreApplication
        Launcher
)
