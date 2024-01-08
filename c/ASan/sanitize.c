#include <stdio.h>
#include <stdlib.h>


/*
    LLVM >= 3.1     GCC >= 4.9.2
    -fsanitize=address (启动ASan)

    -fno-omit-frame-pointer (让栈追溯信息更加友好)
*/

int main(int argc, char **argv) {
/*
    int x[5] = {0};
    x[5] = 10;
    printf("%d \n", x[5]);
    printf("%d \n", x[6]);
*/

    //int *p = NULL;
    //*p = 0;

    char *buffer = (char *)malloc(32);
    memset(buffer, 1, 32);

    free(buffer);

    return EXIT_SUCCESS;
}


