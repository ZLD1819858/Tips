#include "string.h"
#include "stdio.h"
#include "IPD.h"
#include "learn_config.h"
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

int B (void *param) __attribute__((weak)) ;


/*
    这种方法的关键在于理解宏展开的顺序和方式。
    预处理器首先展开所有的参数，然后再执行宏的主体。
    因此，通过间接的方式进行拼接可以实现您所需的功能。
    1. 定义一个宏，将其与__FILE__拼接
    2. 定义一个测试宏
*/
#define CONCAT_FILE_MACRO(macro) macro " " __FILE__
#define INFO_MACRO "This is a test:"

int main (void)
{
    //printf("B function addr: %x\r\n", &B);
    printf("%s\n", CONCAT_FILE_MACRO(INFO_MACRO));
    printf("%s %s\n", CONCAT_FILE_MACRO("test"), __FUNCTION__);

    if (0 == strcmp(CURR_TEST, "a/test.h")) {
        printf_info("yes, is a\n");
    } else {
        printf_warning("no, is b\n");
    }
    //deprecatedFn(); //unavailableFn();
    struct Animal a1 = {"houzi", 11};
    strncpy(a1.name, "hei\0heiahglajlgja", 8);
    printf("%s %d\n", a1.name, a1.age);

    printf("%lld %d\n",sizeof(long), ALIGN_DOWN_AS(1024, 4));

#if defined(LEARN_CONST) && (LEARN_CONST == ON)
    const int a1 = 10;
    const int a2 = 10;
    int * const b1 = &a1;
    b1 = &a2;
    *b1 = 1221UL;
    printf("const value: %d\n", a1);

#endif
    return 0;
}
