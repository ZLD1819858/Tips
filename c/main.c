#include "string.h"
#include "stdio.h"
#include "IPD.h"
#include "learn_config.h"
#include "test.h"


const char BuildInfo[] = "Version: "__DATE__" "__TIME__ ;

#define RL_BUFFER_COUNT 2

/*
    检验宏的奇偶性
*/
#if (!RL_BUFFER_COUNT) || (RL_BUFFER_COUNT & (RL_BUFFER_COUNT - 1))
#error "testte"
#endif

//int __attribute__((deprecated))deprecatedFn(void);
//void unavailableFn(void) __attribute__((unavailable)) ;

struct Animal {
    char name[8];
    int age;
};

/*
    这种方法的关键在于理解宏展开的顺序和方式。
    预处理器首先展开所有的参数，然后再执行宏的主体。
    因此，通过间接的方式进行拼接可以实现您所需的功能。
    1. 定义一个宏，将其与__FILE__拼接
    2. 定义一个测试宏
*/
#define CONCAT_FILE_MACRO(macro) macro " " __FILE__
#define INFO_MACRO "This is a test:"

#define ZHANG1 __COUNTER__
#define ZHANG2 __COUNTER__

int main (void)
{
    printf_info("BuildInfo: %s\n", BuildInfo);
    //printf("B function addr: %x\r\n", &B);
    printf("%s\n", CONCAT_FILE_MACRO(INFO_MACRO));
    printf("%s %s\n", CONCAT_FILE_MACRO("test"), __FUNCTION__);

    if (0 == strcmp(CURR_TEST, "a/test.h")) {
        printf_info("yes, is a\n");
    } else {
        printf_warning("no, is b\n");
    }

    printf_info("%d %d\n", ZHANG1, ZHANG2);

    return 0;
}
