#include "IPD.h"
#include "stdio.h"
//#include "string.h"
//#include "test.h"


int main(int argc, char **argv) {

    u8 arr1[10] = {1};
    for (int i = 0; i < sizeof(arr1); i++) {
        printf("%d\n", arr1[i]);
    }
    memset(&arr1[0], 99, sizeof(arr1));
    for (int i = 0; i < sizeof(arr1); i++) {
        printf("%d\n", arr1[i]);
    }

    return 0;
}