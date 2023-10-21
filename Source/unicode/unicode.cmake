set(Unicode_DIR ${CMAKE_CURRENT_LIST_DIR})

project(Unicode)
file(GLOB_RECURSE Unicode_Sources "${Unicode_DIR}/public/*.h" "${Unicode_DIR}/private/*.h" "${Unicode_DIR}/public/*.cpp" "${Unicode_DIR}/private/*.cpp")
add_library(Unicode STATIC ${Unicode_Sources})
target_include_directories(Unicode
        PUBLIC
        "${Unicode_DIR}/public"
        PRIVATE
        "${Unicode_DIR}/private"
        INTERFACE
        "${Unicode_DIR}/public"
)
target_link_libraries(Unicode
        PUBLIC
        Qt${QT_VERSION_MAJOR}::Core
        Data
        boost_locale
)
