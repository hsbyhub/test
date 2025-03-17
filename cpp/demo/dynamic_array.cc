#include <cstdint>
#include <iostream>

struct Foo {
    char val;
    uint32_t arr[];
};

int main() {
    Foo foo;
    std::cout << "Size of Foo is " << std::to_string(sizeof(foo)) << std::endl;
}
