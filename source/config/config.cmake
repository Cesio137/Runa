set(Config_DIR ${CMAKE_CURRENT_LIST_DIR})

project(Config)
file(GLOB_RECURSE Config_Sources "${Config_DIR}/public/*.h" "${Config_DIR}/private/*.h" "${Config_DIR}/public/*.cpp" "${Config_DIR}/private/*.cpp")
add_library(Config STATIC ${Config_Sources})
target_include_directories(Config
        PUBLIC
        "${Config_DIR}/public"
        PRIVATE
        "${Config_DIR}/private"
        INTERFACE
        "${Config_DIR}/public"
)
target_link_libraries(Config
        Qt${QT_VERSION_MAJOR}::Core
)
