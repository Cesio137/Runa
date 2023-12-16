#include <iostream>
#include <RenderHardwareInterface.h>

int main(int argc, char* argv[])
{
    std::cout << "Hello, World!" << std::endl;
    RenderHardwareInterface* RHI = new RenderHardwareInterface();
    RHI->Init(0);
    return 0;
}
