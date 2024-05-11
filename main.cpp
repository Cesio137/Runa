#include <iostream>
#include <RenderInterface.h>

int main(int argc, char* argv[])
{
    Nanometro::RenderInterface RHI(OPENGL_INIT_330);
    int code = RHI.exec();
    if (!code)
        std::cout << RHI.GetErrorLog() << "\n";

    return code;
}
