FetchContent_GetProperties(joltphysics)
if(NOT joltphysics_POPULATED)
    FetchContent_Declare(
      joltphysics
        GIT_REPOSITORY https://github.com/jrouwe/JoltPhysics.git
        GIT_TAG        v4.0.0 # 4.0.0
        GIT_PROGRESS TRUE
        SOURCE_SUBDIR  Build
      )
  
    FetchContent_MakeAvailable(joltphysics)
    set_property(TARGET Jolt PROPERTY COMPILE_WARNING_AS_ERROR OFF)
    target_compile_options(Jolt PUBLIC /WX-)
    set_target_properties(Jolt PROPERTIES FOLDER Plugins)
endif()