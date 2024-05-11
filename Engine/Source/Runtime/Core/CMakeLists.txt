set(Core_DIR ${CMAKE_CURRENT_LIST_DIR})
find_package(SDL2 CONFIG REQUIRED)

project(Core)
file(GLOB_RECURSE Core_Sources "${Core_DIR}/Public/*.h" "${Core_DIR}/Public/*.cpp" "${Core_DIR}/Private/*.h" "${Core_DIR}/Private/*.cpp")
add_library(Core STATIC ${Core_Sources})
target_include_directories(Core
        PUBLIC
        "${Core_DIR}/Public"
        PRIVATE
        "${Core_DIR}/Private"
)

set_target_properties(Core PROPERTIES FOLDER "Engine/Source/Runtime" LINKER_LANGUAGE CXX)