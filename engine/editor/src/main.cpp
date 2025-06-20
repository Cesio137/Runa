#include <iostream>
#include <utils/system/path.h>

int main(int argc, char** argv) {
    std::cout << "Hello, world!" << std::endl;
    vec_cstr vec = vec_cstr_init();
    vec_cstr_push(&vec, cstr_from("hello"));
    vec_cstr_push(&vec, cstr_from("world"));
    cstr path = runaJoinPaths(vec);
    vec_cstr_drop(&vec);
    std::cout << cstr_str(&path) << std::endl;
    cstr_drop(&path);
    return 0;
}
