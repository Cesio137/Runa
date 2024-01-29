#include <iostream>
#include <Launcher.h>

int main(int argc, char* argv[])
{
    std::cout << "Hello, World!" << std::endl;

    Nanometro::Launcher* RHI = new Nanometro::Launcher();

    return RHI->Init(0);
}
