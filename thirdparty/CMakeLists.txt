set(THIRDPARTY_DIR ${CMAKE_CURRENT_LIST_DIR})

#Configure glad library
include(${THIRDPARTY_DIR}/glad/glad.cmake)

#Configure ICU
include(${THIRDPARTY_DIR}/icu/icu.cmake)

#Set folder and group all thirdparty projects

function(get_all_targets var)
    set(targets)
    get_all_targets_recursive(targets ${CMAKE_CURRENT_SOURCE_DIR})
    set(${var} ${targets} PARENT_SCOPE)
endfunction()

macro(get_all_targets_recursive targets dir)
    get_property(subdirectories DIRECTORY ${dir} PROPERTY SUBDIRECTORIES)
    foreach(subdir ${subdirectories})
        get_all_targets_recursive(${targets} ${subdir})
    endforeach()

    get_property(current_targets DIRECTORY ${dir} PROPERTY BUILDSYSTEM_TARGETS)
    list(APPEND ${targets} ${current_targets})
endmacro()

get_all_targets(all_targets)
message("All targets: ${all_targets}")

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_target_properties(${all_targets} PROPERTIES FOLDER thirdparty)
