FetchContent_GetProperties(Bullet)
if(NOT Bullet_POPULATED)
    FetchContent_Declare(
        Bullet
        GIT_REPOSITORY https://github.com/bulletphysics/bullet3.git
        GIT_TAG        7dee3436e747958e7088dfdcea0e4ae031ce619e # 3.2.4
      )
  
    FetchContent_MakeAvailable(Bullet)
endif()