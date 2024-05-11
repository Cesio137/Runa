#include <iostream>
#include <RenderInterface.h>

int main(int argc, char* argv[])
{
    Nanometro::RenderInterface RHI(OPENGL_INIT_330);
    int code = RHI.exec();
    size_t size = sizeof(RHI);
    std::cout << size << "\n";
    if (!code)
        std::cout << RHI.GetErrorLog() << "\n";
    return code;
}
