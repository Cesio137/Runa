FetchContent_GetProperties(flecs)
if(NOT flecs_POPULATED)
    FetchContent_Declare(
        flecs
        GIT_REPOSITORY https://github.com/SanderMertens/flecs.git
        GIT_TAG        v3.2.9 #3.2.9
        GIT_PROGRESS TRUE
    )
  
    FetchContent_MakeAvailable(flecs)

    get_all_targets(flecs_targets)
    message("All targets: ${flecs_targets}")

    set_property(GLOBAL PROPERTY USE_FOLDERS ON)
    set_target_properties(${flecs_targets} PROPERTIES FOLDER Thirdparty)
endif()