FetchContent_GetProperties(rapidjson)
if(NOT rapidjson_POPULATED)
    FetchContent_Declare(
        rapidjson
        GIT_REPOSITORY https://github.com/Tencent/rapidjson.git
        GIT_TAG        v1.1.0 # 1.1.0
        GIT_PROGRESS TRUE 
      )
  
    FetchContent_MakeAvailable(rapidjson)
endif()