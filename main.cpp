#include <iostream>
#include <RenderInterface.h>

int main(int argc, char* argv[])
{
    Nanometro::RenderInterface RHI(OPENGL_INIT_460);
    size_t size = sizeof(RHI);
    int code = RHI.exec();
    std::cout << size << "\n";
    if (!code)
        std::cout << RHI.GetErrorLog() << "\n";
    return code;
}
