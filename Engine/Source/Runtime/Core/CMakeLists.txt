set(Core_DIR ${CMAKE_CURRENT_LIST_DIR})

project(Core)
file(GLOB_RECURSE Core_Sources "${Core_DIR}/*.h" "${Core_DIR}/*.cpp")
add_library(Core STATIC ${Core_Sources}
        CoreMinimal.h)
target_include_directories(Core
        PUBLIC
        "${Core_DIR}/"
)
target_link_libraries(Core
        Data
        Config
        Nlohmann
)

set_target_properties(Core PROPERTIES FOLDER "Source")