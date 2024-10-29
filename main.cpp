#include <iostream>
#include <RenderInterface.h>

using namespace Nanometro;

int main(int argc, char* argv[])
{
    RenderInterface RHI(OPENGL_INIT_330);
    int code = RHI.exec();
    if (code != 0) {
        std::cout << RHI.GetErrorLog() << "\n";
        return code;
    }

    return 0;
}
