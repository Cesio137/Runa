#include <iostream>
#include <CoreApplication.h>
#include <System/Dir.h>
#include <System/Enviroment.h>

int main(int argc, char *argv[]) {
    std::cout << "Hello, world!" << std::endl;
    String homedir = Enviroment::GetVariable("USERPROFILE");
    std::cout << homedir << std::endl;
    CoreApplication core(argc, argv);
    return core.exec();
}
