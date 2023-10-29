#include <stdio.h>
#include <math.h>



int s1 = 0xC0000000;
unsigned int uns1 = 0xC0000000;

int main(int argc, char **argv)
{
    double x = sqrt(2.0);
    int heihei = 0b001011;
    printf("square 2.0 of %f %d\n", x, heihei);
    printf("%s %s heihei\n",argv[0], argv[3]);

    printf("i32>>1:0x%X\nu32>>1:0x%x\n", s1>>1, uns1>>1);
    printf("i32<<1:0x%X\nu32<<1:0x%x\n", s1<<1, uns1<<1);
    return 0;
}

