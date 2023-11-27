FetchContent_GetProperties(box2d)
if(NOT box2d_POPULATED)
    FetchContent_Declare(
            box2d
            GIT_REPOSITORY https://github.com/erincatto/box2d.git
            GIT_TAG        v2.4.1 #2.4.1
            GIT_PROGRESS TRUE
    )

    FetchContent_MakeAvailable(box2d)
    set_target_properties(box2d PROPERTIES FOLDER Plugins)
endif()