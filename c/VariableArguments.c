/*
        变长参数后面可以跟着若干个不定参数。不定参数在函数中形参用...来表示，
    然后在这个函数体中使用 va_start、va_arg、va_end这3个宏定义方法来承接
    不定参数，但是在承接不定参数时，要承接多少个是需要函数传参的同时，也将
    不定参数的个数传进来。
*/

#include <stdio.h>
#include <stdarg.h>

int adds(int num, ...) {
    int sum = 0;
    va_list args;

    va_start(args, num);
    while (num--) {
        sum += va_arg(args, int);
    }
    va_end(args);

    return sum;
}

int main(int argc, char **argv)
{
    printf("sum = %d\n", adds(5,32,4242,15,667,2));
    printf("sum = %d\n", adds(3,15,667,2));

    return 0;
}

