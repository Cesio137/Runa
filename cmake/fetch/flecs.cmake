FetchContent_GetProperties(flecs)
if(NOT flecs_POPULATED)
    FetchContent_Declare(
        flecs
        GIT_REPOSITORY https://github.com/SanderMertens/flecs.git
        GIT_TAG        ae0bed2815127d3c8315e9e4c3edb253ea8a91c4 #3.2.7
    )
  
    FetchContent_MakeAvailable(flecs)
endif()