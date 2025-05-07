FetchContent_Declare(
    EASTL
    GIT_REPOSITORY https://github.com/electronicarts/EASTL.git
    TAG 3.21.23
)

FetchContent_MakeAvailable(EASTL)
set_target_properties(EASTL PROPERTIES FOLDER "/engine/thirdparty/EASTL")