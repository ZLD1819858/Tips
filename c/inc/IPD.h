#ifndef __IPD_H_
#define __IPD_H_

#include "stddef.h"

typedef char                i8;
typedef short int           i16;
typedef int                 i32;
typedef long long           i64;
typedef long                isize;
typedef unsigned char       u8;
typedef unsigned short int  u16;
typedef unsigned int        u32;
typedef unsigned long long  u64;
typedef unsigned long       usize;

#define                     TYPEDEF_AND_REF(name)\
    typedef struct name name;\
    typedef name *name##Ref;


#ifndef IPD_CALC_ARG_MAX

#define __ARGS(X) (X)

#define __ARGC_N(_0,_1,_2,_3,_4,_5,_6,_7,N,...)     N

#define __ARGC(...)                                 __ARGS(__ARGC_N(__VA_ARGS__,8,7,6,5,4,3,2,1))

#define __ARG0(_0,...)                              _0
#define __ARG1(_0,_1,...)                           _1
#define __ARG2(_0,_1,_2,...)                        _2
#define __ARG3(_0,_1,_2,_3,...)                     _3
#define __ARG4(_0,_1,_2,_3,_4,...)                  _4
#define __ARG5(_0,_1,_2,_3,_4,_5,...)               _5
#define __ARG6(_0,_1,_2,_3,_4,_5,_6,...)            _6
#define __ARG7(_0,_1,_2,_3,_4,_5,_6,_7,...)         _7

#define __VA0(...)                                  __ARGS(__ARG0(__VA_ARGS__,0)+0)
#define __VA1(...)                                  __ARGS(__ARG1(__VA_ARGS__,0,0))
#define __VA2(...)                                  __ARGS(__ARG2(__VA_ARGS__,0,0,0))
#define __VA3(...)                                  __ARGS(__ARG3(__VA_ARGS__,0,0,0,0))
#define __VA4(...)                                  __ARGS(__ARG4(__VA_ARGS__,0,0,0,0,0))
#define __VA5(...)                                  __ARGS(__ARG5(__VA_ARGS__,0,0,0,0,0,0))
#define __VA6(...)                                  __ARGS(__ARG6(__VA_ARGS__,0,0,0,0,0,0,0))
#define __VA7(...)                                  __ARGS(__ARG7(__VA_ARGS__,0,0,0,0,0,0,0,0))

#define IPD_CALC_ARG_MAX         8
#define ARGC(...)       __ARGC(__VA_ARGS__)
#define ARGS(x, ...)    __VA##x(__VA_ARGS__)
#endif  /* IPD_CALC_ARG_MAX */


#define    printf_info(...)    do{\
                                   printf("\033[0m");/* Reset all attribute */\
                                   printf("\033[32m[I] ");\
                                   printf(__VA_ARGS__);\
                                   printf("\033[0m");\
                                 } while(0)
#define    printf_warning(...) do{\
                                   printf("\033[0m");/* Reset all attribute */\
                                   printf("\033[33m[W] ");\
                                   printf(__VA_ARGS__);\
                                   printf("\033[0m");/* Reset all attribute */\
                                 } while(0)
#define    printf_error(...)   do{\
                                   printf("\033[0m");/* Reset all attribute */\
                                   printf("\033[31m[E] ");\
                                   printf(__VA_ARGS__);\
                                   printf("\033[0m");/* Reset all attribute */\
                                 } while(0)


#define msleep(ms)      usleep(ms*1000)

/* Compiler adaptation */
#ifdef __GNUC__
    #define ATTR_ALIGN(x)       __attribute__((aligned((x))))
#elif __TASKING__
    #define ATTR_ALIGN(x)       __attribute__((aligned((x))))
#endif /* Compiler adaptation */

#ifdef __GNUC__
    #define LOCAL_INLINE static inline
#endif

#define ALIGN_UP(x)                         (((x) + 3) & (~3))
#define ALIGN_DOWN(x)                       ((x) & (~3))

#define ALIGN_UP_AS(x, align_digital)        (((x) + ((align_digital) - 1)) & (~((align_digital) - 1)))
#define ALIGN_DOWN_AS(x, align_digital)      ((x) & (~((align_digital) - 1)))

#define TRUE                                (0 == 0)
#define FALSE                               (0 == 1)
#define IPD_NULL                                ((void*)0)

#define max(x, y) ({                \
    typeof(x) _max1 = (x);          \
    typeof(y) _max2 = (y);          \
    (void) (&_max1 == &_max2);   /* This line has no effect on execution, it just uses the compiler to check type consistency. */   \
    _max1 > _max2 ? _max1 : _max2; })
#define min(x, y) ({                \
    typeof(x) _min1 = (x);          \
    typeof(y) _min2 = (y);          \
    (void) (&_min1 == &_min2);   /* This line has no effect on execution, it just uses the compiler to check type consistency. */   \
    _min1 < _min2 ? _min1 : _min2; })

#define ON                                  (1)
#define OFF                                 (0)

#define OFFSET_OF(type, member)           ((unsigned long)(&(((type *)0)->member)))
#define CONTAINER_OF(ptr, type, member)   ((type *)((char *)(ptr) - Z_OFFSET_OF(type, member)))

#define offset_of(type, member) \
    ((unsigned long)(&((type *)0)->member))


#define container_of(ptr, type, member) \
    ((type *)((char *)(ptr) - (unsigned long)(&((type *)0)->member)))

#define assert(expression) ((void)0)
#if defined(N0DEBUG)
#undef assert
#define assert(expression) ((expression) ?  \
                            (void)0 :       \
                            assert_failed(__FILE__, __func__, __LINE__))

void assert_failed(const char *file, const char *func, int line)
{
    printf("Assertion failed at %s(%s):%d", file, func, line);
}


/*
static inline void * __cdecl memset(void *_Dst,int _Val, size_t _Size) {

}
static inline void * __stdcall memset2(void *_Dst,int _Val, size_t _Size) {

}
*/

#endif /*__IPD_H_*/
