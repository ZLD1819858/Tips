#include "stdio.h"

int main(int argc, char **argv) {
    int x[5] = {0};
    x[5] = 10;
    printf("%d \n", x[5]);
    printf("%d \n", x[6]);
    return 0;
}


