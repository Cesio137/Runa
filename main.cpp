#include <iostream>
#include <Launcher.h>

int main(int argc, char* argv[])
{
    std::cout << "Hello, World!" << std::endl;
    Launcher* RHI = new Launcher();
    RHI->Init(0);
    return 0;
}
