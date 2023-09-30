FetchContent_GetProperties(joltphysics)
if(NOT joltphysics_POPULATED)
    FetchContent_Declare(
      joltphysics
        GIT_REPOSITORY https://github.com/jrouwe/JoltPhysics.git
        GIT_TAG        3d36f7aea85fcea4b0de5404c953e40db0a749ba # 3.0.1
        SOURCE_SUBDIR  Build
      )
  
    FetchContent_MakeAvailable(joltphysics)
    set_property(TARGET Jolt PROPERTY COMPILE_WARNING_AS_ERROR OFF)
    target_compile_options(Jolt PUBLIC /WX-)
endif()