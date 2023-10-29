#include "stdio.h"

typedef unsigned char uint8_t;

struct person
{
    int age;
    int sex;
    int name;
    int no;
    char a;
    char b;
    int c;
};
typedef struct person* person_t;

#define ALIGN_SIZE 4
#define ALIGN_UP(x)     (((x)+ALIGN_SIZE-1) & ~(ALIGN_SIZE -1))
#define ALIGN_DOWN(x)   ((x) & ~(ALIGN_SIZE - 1))

void *rt_memmove(void *dest, const void *src, unsigned int n)
{
    char *tmp = (char *)dest, *s = (char *)src;
    unsigned int  len = n;

    if ((s < tmp) && (tmp < (s + n)))
    {
        tmp += len;
        s += len;

        while (len--)
        {
            *(--tmp) = *(--s);
        }
    }
    else
    {
        while (len--)
        {
            *tmp++ = *s++;
        }
    }

    return dest;
}


int rt_memcmp(const void *cs, const void *ct, unsigned int count)
{
    const unsigned char *su1 = 0, *su2 = 0;
    int res = 0;

    for (su1 = (const unsigned char *)cs, su2 = (const unsigned char *)ct; 0 < count; ++su1, ++su2, count--)
    {
        if ((res = *su1 - *su2) != 0)
        {
            break;
        }
    }

    return res;
}

int rt_strlen(const char *s)
{
    const char *sc = 0;

    for (sc = s; *sc != '\0'; ++sc) /* nothing */
    {
        ;
    }
    return sc - s;
}

int rt_strcmp(const char *cs, const char *ct)
{
    while (*cs && *cs == *ct)
    {
        cs++;
        ct++;
    }

    return (*cs - *ct);
}

int rt_strncmp(const char *cs, const char *ct, unsigned int count)
{
    register signed char __res = 0;

    while (count)
    {
        if ((__res = *cs - *ct++) != 0 || !*cs++)
        {
            break;
        }
        count --;
    }

    return __res;
}

int rt_strnlen(const char *s, unsigned int maxlen)
{
    const char *sc = 0;

    for (sc = s; *sc != '\0' && (unsigned int )(sc - s) < maxlen; ++sc) /* nothing */
    {
        ;
    }

    return sc - s;
}

char *rt_strncpy(char *dst, const char *src, unsigned int n)
{
    if (n != 0)
    {
        char *d = dst;
        const char *s = src;

        do
        {
            if ((*d++ = *s++) == 0)
            {
                /* NUL pad the remaining n-1 bytes */
                while (--n != 0)
                {
                    *d++ = 0;
                }
                break;
            }
        } while (--n != 0);
    }
    return (dst);
}

typedef struct abc{
    int a;
    int b;
}abc;

int lllll(abc a)
{
    a.a = 2;
    return 0;
}

int main(void)
{
    person_t A1;
    person_t const A2;

    A1->age = 22;
    A2->age = 22;
    A2->age = 21;

    printf("var: %d\r\n",A1->age);
    printf("var: %d\r\n",A2->age);

    printf("====================================\r\n");


    char str1[] = "zhang";
    char str2[] = "luo";
    char str3[] = "dong";

    //指向字符常量的指针
    const char *ptr1;
    //等价上述定义
    char const *ptr2;
    //指向字符的指针常数
    char* const ptr3 = str3;

    
    ptr1 = str1;

    printf("%s\r\n",ptr1);
    printf("%c\r\n",ptr1[2]);

    str1[2] = 'b';
    str2[2] = 'b';

    ptr1 = str2;
    printf("%s\r\n",ptr1);

    printf("%s\r\n",ptr3);
    printf("%s\r\n",str3);
    str3[2] = 'b';
    ptr3[2] = 'p';
    printf("%s\r\n",ptr3);

    printf("================指针进阶====================\r\n");
    printf("uint8_t的大小：%d byte\r\n", sizeof(uint8_t));

    int ret = 3;
    int *ret_p1 = &ret;
    int *ret_p2 = &ret_p1;
    int **ret_p3 = &ret_p1;
    printf("%d\r\n",ret_p1);
    printf("%d\r\n",*ret_p1);
    printf("%d\r\n",ret_p2);
    printf("%d\r\n",*ret_p2);
    printf("%d\r\n",*(int *)(*ret_p2));
    printf("%d\r\n",**ret_p3);


    printf("%d %d\r\n",sizeof(struct person), ALIGN_DOWN(sizeof(struct person)));
    printf("%d %d\r\n",sizeof(person_t), ALIGN_DOWN(sizeof(person_t)));
    int aaa = 0x11111111;
    printf("%d %d %d\r\n",sizeof(int *),sizeof(char *), &aaa );
    printf("%d %d %d\r\n",sizeof(int *),sizeof(char *), (&aaa) );

    signed char test_mov1 = 0x97;
    signed char test_mov2 = 0x17;

    test_mov1 = test_mov1 >> 4;
    test_mov2 = test_mov2 >> 4;
    printf("%#x %#x\r\n",test_mov1, test_mov2);

    __attribute__((__aligned__(8)))
    int a  = 20;
    int b  = 20;
    printf("地址：%#x\r\n",&a);
    printf("地址：%#x\r\n",&b);

    uint8_t *zld_1;
    int zld_2 = 22424;
    *zld_1 = 22     ;
    zld_1 = &zld_2;
    printf("地址：%#x %d %d\r\n", zld_1, *zld_1, sizeof("sa"));

    printf("%d\r\n",'i');
    printf("%d\r\n",rt_strncmp("unittest", "un", 5));
    
    if(!'\0')
    {
        printf("test\r\n");
    }

    printf("%d\r\n", rt_strnlen("zl 1",3));

    char *s1 = "zhang";
    char *s2 = s1;
    s2++;
    printf("字符串1：%s\t长度：%d\r\n字符串2：%s\t长度%d\r\n", s1, rt_strlen(s1), s2, rt_strlen(s2));
    printf("%d\r\n",s2-s1);

    printf("%d\r\n",'a'-'r');

    int s3_1 = 111;
    int *s3 = &s3_1;
    int *s4;
    printf("%d\r\n", s3+1+1+1);
    printf("%x\r\n", &s3);
    printf("%d\r\n", (*s3)+1);//有问题

    char *memcmp_1 = "red";
    char *memcmp_2 = "apple";

    printf("%d\r\n",rt_memcmp(memcmp_1, memcmp_2, 5));

    char *memmove_1;

    int aagag = 2222;
    int bb = 23252;
    char *memmove_2 = "zhang";
    rt_memmove(memmove_1, memmove_2, 2);
    printf("%s\r\n", memmove_1);

    llll(0);

    return 0;
}
