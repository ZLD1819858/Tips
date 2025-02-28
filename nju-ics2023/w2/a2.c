#include <stdio.h>

#define A sys ## tem

int main(int argc, char **argv)
{
    A("echo Hello\n");
    system("cat a2.c\n");
    return 0;
}

