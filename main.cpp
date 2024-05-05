#include <iostream>
#include <Launcher.h>

int main(int argc, char* argv[])
{
    std::shared_ptr<Nanometro::Launcher> RHI = std::make_shared<Nanometro::Launcher>();

    return RHI->Init(0);
}
