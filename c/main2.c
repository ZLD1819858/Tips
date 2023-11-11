#include <stdio.h>

int main(int argc, char **argv)
{
    int i = 0;
    float *a = (float *)&i;
    float b = *a;

    char *str = "heihei";
    str[0] = 'a';
printf("%d %f %s\n", i,b,str);
    return 0;
}
