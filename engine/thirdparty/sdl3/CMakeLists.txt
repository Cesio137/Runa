FetchContent_Declare(
    SDL3
    URL                 https://github.com/libsdl-org/SDL/releases/download/preview-3.1.6/SDL3-3.1.6.tar.gz
)

set(SDL_SHARED OFF CACHE INTERNAL "")
set(SDL_STATIC ON CACHE INTERNAL "")

FetchContent_MakeAvailable(SDL3)