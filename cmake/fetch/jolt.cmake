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

    get_all_targets(jolt_targets)
    message("All targets: ${jolt_targets}")

    set_property(GLOBAL PROPERTY USE_FOLDERS ON)
    set_target_properties(${jolt_targets} PROPERTIES FOLDER Plugins)
endif()