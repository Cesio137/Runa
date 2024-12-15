set(SOL_DIR ${CMAKE_CURRENT_LIST_DIR})

project(sol)
file(GLOB_RECURSE SOL_SOURCES "${SOL_DIR}/include/*.hpp")
add_library(sol INTERFACE ${SOL_SOURCES})
target_include_directories(sol
        INTERFACE
        "${SOL_DIR}/include"
)
target_link_libraries(sol
        INTERFACE
        lua
)
set_target_properties(sol PROPERTIES FOLDER "/engine/source/thirdparty" LINKER_LANGUAGE CXX)