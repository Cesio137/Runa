#pragma once

#include <SDL3/SDL.h>
#include <utility>
#include "config.h"

namespace Runa {
    enum ESDL_Driver : uint8_t {
        ES_320 = 0,
        CORE_330 = 1,
        CORE_460 = 2,
        VULKAN = 3,
        D3D11 = 4,
        D3D12 = 5,
    };

    struct FSDL_Backend {
        ~FSDL_Backend() {
            if (renderer_ptr)
                SDL_DestroyRenderer(renderer_ptr);
            if (window_ptr)
                SDL_DestroyWindow(window_ptr);
        }

        SDL_Window *window_ptr;
        SDL_Renderer *renderer_ptr;
    };

    int InitDriver(FSDL_Backend &backend, ESDL_Driver driver = ESDL_Driver::CORE_330);
    std::pair<uint8_t, uint8_t> GetLatestOpenglVersionSupported();
}
