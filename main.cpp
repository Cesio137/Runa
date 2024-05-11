#include <iostream>
#include <RenderInterface.h>

int main(int argc, char* argv[])
{
    Nanometro::RenderInterface interface(OPENGL_INIT_330);
    int code = interface.exec();
    if (!code)
        std::cout << interface.GetErrorLog() << "\n";

    return code;
}
