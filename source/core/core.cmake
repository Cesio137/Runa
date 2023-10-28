set(Core_DIR ${CMAKE_CURRENT_LIST_DIR})

project(Core)
file(GLOB_RECURSE Core_Sources "${Core_DIR}/public/*.h" "${Core_DIR}/private/*.h" "${Core_DIR}/public/*.cpp" "${Core_DIR}/private/*.cpp")
add_library(Core STATIC ${Core_Sources})
target_include_directories(Core
        PUBLIC
        "${Core_DIR}/public"
        INTERFACE
        "${Core_DIR}/public"
)
target_link_libraries(Core
        Qt${QT_VERSION_MAJOR}::Core
        Launcher
        Unicode
)
