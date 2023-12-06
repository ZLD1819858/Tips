//#include "hello.h"
#include <stdio.h>
#include "string.h"
#include "IPD.h"
#include "test.h"


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


int main (void)
{
    deprecatedFn();
    unavailableFn();
    struct Animal a1 = {"houzi", 11};
    strncpy(a1.name, "hei\0heiahglajlgja", 8);
    printf("%s %d\n", a1.name, a1.age);

    printf("%d %d\n",sizeof(long), ALIGN_DOWN_AS(1024, 4));
    int aaa = 150;
    printf("%lu.%lu\n",aaa/100, aaa%100);
    return 0;
}
