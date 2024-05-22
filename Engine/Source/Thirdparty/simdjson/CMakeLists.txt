set(Simdjson_DIR ${CMAKE_CURRENT_LIST_DIR})

project(Simdjson)
file(GLOB_RECURSE Simdjson_Sources "${Simdjson_DIR}/Public/*.h")
add_library(Simdjson INTERFACE ${Simdjson_Sources})
target_include_directories(Simdjson
        INTERFACE
        "${Simdjson_DIR}/Public"
)

set_target_properties(Simdjson PROPERTIES FOLDER "Engine/Source/Thirdparty")