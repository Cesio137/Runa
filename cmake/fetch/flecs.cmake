FetchContent_GetProperties(flecs)
if(NOT flecs_POPULATED)
    FetchContent_Declare(
        flecs
        GIT_REPOSITORY https://github.com/SanderMertens/flecs.git
        GIT_TAG        v3.2.8 #3.2.7
        GIT_PROGRESS TRUE
    )
  
    FetchContent_MakeAvailable(flecs)
endif()