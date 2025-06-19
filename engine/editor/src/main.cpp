#include <iostream>
#include <core/system/path.h>

int main(int argc, char** argv) {
    std::cout << "hello world!" << std::endl;
    const char *paths[] = { "ola", "mundo" };
    char* conc_str = runaJoinPaths(paths, 2);
    std::cout << conc_str << std::endl;
    return 0;
}
