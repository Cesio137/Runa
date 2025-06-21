#include <iostream>
#include <render/sdl_glrender.h>

using namespace runa::render;

int main(int argc, char** argv) {
    std::cout << "Hello, world!" << std::endl;
    sdl_glrender_c rhi = sdl_glrender_c();
    rhi.run(sdl_gldriver_t::GL_DRIVER_OPENGLCORE);
    return 0;
}
