#include <stdio.h>

static const char srcvers[] __attribute__((used)) = "VERSION/foo.c";

static int arr1[10];
int arr2[10]= {1};

const int arr3[3] = {0};

static int add(int a) {
    return a + 1;
}
int z_add(int a) __attribute__((alias("add")));


int main(int argc, char **argv)
{
    printf("test: %d\n", TEST);

    return 0;
}

