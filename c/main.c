//#include "hello.h"
#include "stdio.h"


struct Animal {
    char name[8];
    int age;
};

int main (void)
{
    //hello ("world");

    struct Animal a1 = {"houzi", 11};
    strncpy(a1.name, "hei\0heiahglajlgja", 8);
    printf("%s %d\n", a1.name, a1.age);
    return 0;
}
