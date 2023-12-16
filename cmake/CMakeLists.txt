include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)
set(FETCHCONTENT_DIR ${CMAKE_CURRENT_LIST_DIR})

file(GLOB_RECURSE cmake_files "*.cmake")
foreach(file ${cmake_files})
    #... calculate ${i} to get the test name
    add_test(validate_${i}, "validator", ${file})
    include(${file})
endforeach()