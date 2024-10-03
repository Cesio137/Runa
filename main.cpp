#include <iostream>
#include <RenderInterface.h>

using namespace Nanometro;

int main(int argc, char* argv[])
{
    RenderInterface RHI(OPENGL_INIT_460);
    int code = RHI.exec();
    if (!code) {
        std::cout << RHI.GetErrorLog() << "\n";
        return code;
    }

    return code;
}
