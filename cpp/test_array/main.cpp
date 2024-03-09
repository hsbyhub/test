#include <stdio.h>

int main() {
    int arr[256] = {-1};
    for (auto x : arr) {
        printf("%d \n", x);
    }
}
