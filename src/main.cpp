#include <iostream>
#include <CoreApplication.h>
#include <Container/String.h>

int main(int argc, char *argv[]) {
    std::cout << "Hello, world!" << std::endl;
    String teste = "Caixa Alta";
    std::cout << teste.toUpper() << std::endl;
    CoreApplication core(argc, argv);
    return core.exec();
}
