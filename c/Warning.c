#include "stdio.h"
#include "unistd.h"

// 通过typeof获取类型做强转来实现编译期间检查类型不一致的问题
#define max(x,y) ({ \
    typeof(x) _x = (x);\
    typeof(y) _y = (y);\
    (void)(&_x == &_y); \
    _x > _y?_x:_y;\
    })


#pragma pack(8) // pack(x) x=1/2/4/8
struct Person {
    char a1;
    char a2;
    char a222;
    int a3;
//} __attribute__((packed));
};

#pragma pack() // pack(x) x=1/2/4/8

struct Person2 {
    char a1;
    char a2;
    char a222;
    int a3;
    char aa;
    char ag;
//} __attribute__((packed));
//};
} __attribute__((aligned(128)));



int main(int argc, char **argv) {

    printf("%ld %ld\n", sizeof(struct Person), sizeof(struct Person2));
    int a = 0;
    //int *b = (int *)a;

    int x = 0;
    typeof(x) y;
    y = 22;
    printf("%d\n", y);

    int z = max(11,2);
    int z2 = max(11,(char)2);

    char *p1;
    typeof (*p1) ch = 'a'; //ch为char类型，不是char *类型。
    printf("%ld, %c\n", sizeof(ch), ch);//1, a

    //其它用法2
    char *p2;
    typeof (p2) p = "hello world";//此时的p才是char *类型，由于在64位机器上，所以指针大小为8字节
    printf("%ld, %s\n", sizeof(p), p);//8, hello world

    while(1) {
        printf("sleep...\n");
        sleep(1);
    }
    return 0;
}
