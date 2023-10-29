#include "stdio.h"

// max为参数个数的上限，allow_0为时候支持获取空参数个数
int arg_generate(int max, int allow_0)
{
    int n, i;

    if (max <= 1) return 0;

    printf("#include <stdlib.h>\r\n");
    printf("\r\n");
    printf("#ifndef ARG_MAX\r\n");
    printf("\r\n");
    printf("#define __ARGS(X) (X)\r\n");
    printf("\r\n");
    printf("#define __ARGC_N(");
    for (n = 0; n < max; n++)
    {
        printf("_%d,", n);
    }
    printf("N,...) %s\r\n", allow_0?"N==1?(#_0)[0]!=0:N":"N");
    printf("\r\n");
    printf("#define __ARGC(...) __ARGS(__ARGC_N(__VA_ARGS__");
    for (n = 0; n < max; n++)
    {
        printf(",%d", max - n);
    }
    printf("))\r\n");
    printf("\r\n");
    for (n = 0; n < max; n++)
    {
        printf("#define __ARG%d(", n);
        for (i = 0; i <= n; i++)
        {
            printf("_%d,", i);
        }
        printf("...) _%d\r\n", n);
    }
    printf("\r\n");
    for (n = 0; n < max; n++)
    {
        printf("#define __VA%d(...) __ARGS(__ARG%d(__VA_ARGS__", n, n);
        for (i = 0; i <= n; i++)
        {
            printf(",0");
        }
        printf(")%s)\r\n", n?"":"+0");
    }
    printf("\r\n");
    printf("#define ARG_MAX         %d\r\n", max);
    printf("#define ARGC(...)       __ARGC(__VA_ARGS__)\r\n");
    printf("#define ARGS(x, ...)    __VA##x(__VA_ARGS__)\r\n");
    printf("\r\n");
    printf("#endif\r\n");

    return 1;
}

int main(int argc, char **argv)
{
    arg_generate(4, 0);
    return 0;
}


