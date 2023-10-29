#include "stdio.h"
#include "IPD.h"

/*
    pack(x) x=1/2/4/8
*/


#pragma pack(8)
struct Person0 {
    u8      a0;
    u8      a1;
    u8      a2;
    u32     a3;
//} __attribute__((packed));
};
TYPEDEF_AND_REF(Person0)


#pragma pack() 

struct Person1 {
    u8  a0;
    u8  a1;
    u8  a2;
    u32 a3;
    u8  a4;
    u8  a5;
//} __attribute__((packed));
//};
} __attribute__((aligned(120)));
TYPEDEF_AND_REF(Person1)



int main(int argc, char **argv) {
    Person0 p1;

    printf("%d %d\n", sizeof(Person0), sizeof(Person1));
    return 0;
}
