FetchContent_GetProperties(box2d)
if(NOT box2d_POPULATED)
    FetchContent_Declare(
            box2d
            GIT_REPOSITORY https://github.com/erincatto/box2d.git
            GIT_TAG        v2.4.1 #2.4.1
            GIT_PROGRESS TRUE
    )

    FetchContent_MakeAvailable(box2d)

    get_all_targets(box2d_targets)
    message("All targets: ${box2d_targets}")

    set_property(GLOBAL PROPERTY USE_FOLDERS ON)
    set_target_properties(${box2d_targets} PROPERTIES FOLDER Plugins)
endif()