set(Data_DIR ${CMAKE_CURRENT_LIST_DIR})

project(Data)
file(GLOB_RECURSE Data_Sources "${Data_DIR}/*.h" "${Data_DIR}/*.cpp")
add_library(Data INTERFACE ${Data_Sources})
target_include_directories(Data
        INTERFACE
        "${Data_DIR}/enum"
        "${Data_DIR}/struct"
)

set_target_properties(Data PROPERTIES FOLDER "Engine/Source/Data")