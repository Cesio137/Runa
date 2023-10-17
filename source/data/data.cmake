set(Data_DIR ${CMAKE_CURRENT_LIST_DIR})

project(Data)
file(GLOB_RECURSE Data_Sources "${Data_DIR}/public/*.h")
add_library(Data STATIC ${Data_Sources})
target_include_directories(Data
        PUBLIC
        "${Data_DIR}/public/struct"
        "${Data_DIR}/public/enum"
        "${Data_DIR}/public/type"
        INTERFACE
        "${Data_DIR}/public/struct"
        "${Data_DIR}/public/enum"
        "${Data_DIR}/public/type"
)
target_link_libraries(Data
        Qt${QT_VERSION_MAJOR}::Core
)
