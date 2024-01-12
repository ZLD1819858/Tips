#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*
    LLVM >= 3.1     GCC >= 4.9.2
    -fsanitize=address (启动ASan)

    -fno-omit-frame-pointer (让栈追溯信息更加友好)
*/


char global_arr[9] = {0};

int main(void) {

    
    char local_arr[15] = {0};
    int i = 0;

    for(i = 0; i < 20; i++) {
        global_arr[i] = 3;
    }

    return EXIT_SUCCESS;
}


