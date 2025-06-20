#include <iostream>
#include <utils/system/path.h>


int main(int argc, char** argv) {
    std::cout << "hello world!" << std::endl;
    vec_cstr vec = vec_cstr_init();
    vec_cstr_push(&vec, cstr_from("/ola/"));
    vec_cstr_push(&vec, cstr_from("mundo"));
    cstr path = runaJoinPaths(vec);
    std::cout << cstr_str(&path) << std::endl;
    return 0;
}
