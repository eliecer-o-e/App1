#include <stdio.h>

void tarea(int* c) {
    *c = *c + 3;
    printf("c = %d\n", *c);
}

int main() {
    int c = 5;
    tarea(&c);
    printf("c = %d\n", c);
    return 0;
}