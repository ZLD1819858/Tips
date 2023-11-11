//#include "hello.h"
#include "stdio.h"
#include "IPD.h"


int __attribute__((deprecated))deprecatedFn(void);
int __attribute__((unavailable))unavailableFn(void);

struct Animal {
    char name[8];
    int age;
};

int deprecatedFn(void)
{
    return 0;
}

int __attribute__((unavailable)) unavailableFn(void)
{
    return 0;
}

int __attribute__((weak))B (void *param);

/*
int B(void *param){return 0;}
*/

int main (void)
{
    printf("B function addr: %x\r\n", &B);
    //hello ("world");
    deprecatedFn();
    unavailableFn();
    struct Animal a1 = {"houzi", 11};
    strncpy(a1.name, "hei\0heiahglajlgja", 8);
    printf("%s %d\n", a1.name, a1.age);

    printf("%d\n", ALIGN_DOWN_AS(1024, 4));
    return 0;
}
