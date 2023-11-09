#include <iostream>
#include <CoreApplication.h>

int main(int argc, char *argv[]) {
    std::cout << "Hello, world" << std::endl;
    CoreApplication core(argc, argv);
    return core.exec();
}
