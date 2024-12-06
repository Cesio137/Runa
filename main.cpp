#include <iostream>
#include <RenderInterface.h>

using namespace Runa;

int main(int argc, char *argv[])
{
    RenderInterface RHI(ESDL_Driver::CORE_460);
    int code = RHI.Exec();
    if (code) {
        std::cerr << SDL_GetError() << std::endl;
        return code;
    }
    
    return 0;
}
