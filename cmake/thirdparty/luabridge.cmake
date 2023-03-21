FetchContent_GetProperties(LuaBridge)
if(NOT LuaBridge_POPULATED)
    FetchContent_Declare(
            LuaBridge
            GIT_REPOSITORY https://github.com/vinniefalco/LuaBridge.git
            GIT_TAG        ad32549288433eacfb0dc64cc3a8e4873de31553 # 2.8
    )

    FetchContent_MakeAvailable(LuaBridge)
    #add_subdirectory(${glfw_SOURCE_DIR} ${glfw_BINARY_DIR})
endif()