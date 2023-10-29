#include <stdio.h>

static int add(int a, int b)
{
    return a + b;
}

int z_add(int a, int b) __attribute__((alias("add")));

int main(void)
{
    int var1 = 9;
    int var2 = 77;
    int ret = -1;

    ret = add(var1, var2);

    ret = z_add(ret, var1+var2);


    printf("%s\r\n",ret==((9+77)*2)?"yes!":"no...");
    return 0;
}
