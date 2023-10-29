#include <stdio.h>
#include "syscall.h"

/*
    在C语言中，可以使用({aa;bb;cc;})来实现宏定义带返回值，会返回最后一个;的值。
*/

/* always return 1 */
#define RETURN_MACRO()          ({do {} while(0); 1;})
#define RETURN_MACRO2()         1

/* return a+b */
#define A_PLUS_B_MACRO(a, b)    ({int ret; ret = (a) + (b); ret;})
#define A_PLUS_B_MACRO2(a, b)    ({int ret; ret = add((a), (b)); ret;})

int add (int a, int b) {
    return a+b;
}

int data = 10;

int main(void)
{
    printf("%d\n",data);

    int a = 77, b = 2;
    printf("RETURN_MACRO: %d\n", RETURN_MACRO());
    printf("RETURN_MACRO2: %d\n", RETURN_MACRO2());
    printf("a + b = %d\n", A_PLUS_B_MACRO(a, b));
    printf("a + b = %d\n", A_PLUS_B_MACRO2(a, b));
    return 0;
}

