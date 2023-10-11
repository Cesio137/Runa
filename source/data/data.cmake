set(Data_DIR ${CMAKE_CURRENT_LIST_DIR})

project(Data)
file(GLOB_RECURSE Data_Sources "${Data_DIR}/public/*.h" "${Data_DIR}/private/*.h" "${Data_DIR}/public/*.cpp" "${Data_DIR}/private/*.cpp")
add_library(Data STATIC ${Data_Sources})
target_include_directories(Data
        PUBLIC
        "${Data_DIR}/public"
        INTERFACE
        "${Data_DIR}/public"
)