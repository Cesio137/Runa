FetchContent_GetProperties(boost)
if(NOT boost_POPULATED)
    FetchContent_Declare(
        boost
        GIT_REPOSITORY https://github.com/boostorg/boost.git
        GIT_TAG        boost-1.83.0 # 1.83
        GIT_PROGRESS TRUE 
      )
  
    FetchContent_MakeAvailable(boost)
endif()