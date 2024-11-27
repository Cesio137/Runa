#include <iostream>
#include <RenderInterface.h>

using namespace Nanometro;

int main(int argc, char *argv[])
{
    RenderInterface RHI(EOpenglVersion::CORE_460);
    int code = RHI.Exec();
    if (code) {
        std::cerr <<RHI.GetErrorLog() << std::endl;
        return code;
    }
    
    return 0;
}
