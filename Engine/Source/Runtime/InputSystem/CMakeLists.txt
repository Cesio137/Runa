set(InputSystem_DIR ${CMAKE_CURRENT_LIST_DIR})

project(InputSystem)
file(GLOB_RECURSE InputSystem_Sources "${InputSystem_DIR}/*.h" "${InputSystem_DIR}/*.cpp")
add_library(InputSystem STATIC ${InputSystem_Sources})
target_include_directories(InputSystem
        PUBLIC
        "${InputSystem_DIR}/"
)
target_link_libraries(InputSystem
        PUBLIC
        Core
        PRIVATE
        SDL2
        SDL2main
        glfw

)

set_target_properties(InputSystem PROPERTIES FOLDER "Engine/Source/Runtime")