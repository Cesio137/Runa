FetchContent_GetProperties(Bullet)
if(NOT Bullet_POPULATED)
    FetchContent_Declare(
        Bullet
        GIT_REPOSITORY https://github.com/bulletphysics/bullet3.git
        GIT_TAG        2c204c49e56ed15ec5fcfa71d199ab6d6570b3f5 # 3.2.5
      )
  
    FetchContent_MakeAvailable(Bullet)
endif()