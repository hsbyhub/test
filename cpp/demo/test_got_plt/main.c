#include <stdio.h>

extern int foo(int i);

int main() {
    printf("test 1\n");
    printf("test 2\n");
    foo(3);
    foo(4);
    return 0;
}
