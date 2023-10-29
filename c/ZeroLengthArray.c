#include "stdio.h"
#include "stdlib.h"
#include "IPD.h"

typedef struct {
    int len;
    int reserved[0];
}Buffer1;

typedef struct  {
    int len;
    int *reserved;
}Buffer2;



int arr[20];
struct thread {
    void *sp;
};
typedef struct thread *thread_t;


    struct thread tid1 = {
            .sp = arr+2
    };

thread_t func(u32 from, u32 to) {
    thread_t tid;
    u32 *sp;

    sp = *(u32 **)(from);

    printf("%u %u\n",*(arr+19), &arr);
    printf("test print %u\n",**(u32 **)&(tid1.sp));
    //printf("%u %u\n",*sp, *sp);

    return tid;
}

#define offsetof(TYPE, MEMBER) ((u32) &((TYPE *)0)->MEMBER)
#define RL_PACKED_START
#define RL_PACKED_END


struct rpmsg_hdr_reserved
{
    u16 rfu; /* reserved for future usage */
    u16 idx;
};


inline u32 inline_add(u32 x, u32 y)
{
    int result = x + y;
    return result;
}

#define max(x,y) ({ \
    typeof(x) _x = (x);\
    typeof(y) _y = (y);\
    (void)(&_x == &_y);\
    _x > _y?_x:_y;\
    })

struct Z {
    char name[8];
    i32 age;
};
int main(void)
{
    struct Z zzz = {"zhanga", 2232};
    strcpy(zzz.name, "uoagg");
    strncpy(zzz.name, "abcdefghzhangl",8);
    strcpy(zzz.name, "abcdefghzhangl");
    printf("%d %s %d\n", zzz.age, zzz.name, sizeof(zzz.name));

    printf("===========================\n");
    printf("Buffer1中存在一个0长度数组.\n");
    printf("Buffer2中存在一个指针(32/64Bit).\n");
    printf("Buffer1结构体所占大小(包含一个0长度数组): %d\n", sizeof(Buffer1));
    printf("Buffer2结构体所占大小(包含一个指针): %d\n", sizeof(Buffer2));

    int *temp = malloc(16);
    Buffer1 *buf1_ptr1 = (Buffer1 *)temp;
    Buffer2 *buf2_ptr1 = (Buffer2 *)temp;
    buf1_ptr1->len = 1;
    buf1_ptr1->reserved[0] = 2;
    buf1_ptr1->reserved[1] = 3;
    buf1_ptr1->reserved[2] = 4;
    buf1_ptr1->reserved[3] = 5;
    printf("Buffer2: %p %d %d\n", temp, buf1_ptr1->len, *(temp+1));

    int *ptr_i = malloc(4);
    char *ptr_c = malloc(4);
    short int *ptr_s = malloc(4);
    void *ptr_v = malloc(4);
    printf("(1)chat类型指针加1：\t%p %p\n", ptr_c, ptr_c + 1);
    printf("(1)void类型指针加1：\t%p %p\n", ptr_v, ptr_v + 1);
    printf("(2)short int类型指针加1：\t%p %p\n", ptr_s, ptr_s + 1);
    printf("(4)int类型指针加1：\t%p %p\n", ptr_i, ptr_i + 1);
    printf("(4)Buffer1类型指针加1：\t%p %p\n", buf1_ptr1, buf1_ptr1 + 1);
    printf("(16)Buffer2类型指针加1：\t%p %p\n", buf2_ptr1, buf2_ptr1 + 1);

    printf("测试指针传递参数===============================================\n");
    int i = 0;
    for (i = 0; i < sizeof(arr) / sizeof(int);i++) {
        arr[i] = i;
    }

    func((u32)&tid1.sp, (u32)&tid1.sp);


    void *ptr1 = malloc(sizeof(Buffer1) + 16);
    Buffer1 *buf1 = (Buffer1 *)ptr1;
    buf1->len = 1234;
    buf1->reserved[0] = 88;
    buf1->reserved[1] = 11;
    buf1->reserved[2] = 22;
    buf1->reserved[3] = 99;
    int abc = 0;
    for (abc = 0; abc < 5;abc++)
    {
        printf("%u ", *(int *)((void*)ptr1+(abc*4)));
    }

    return 0;
}