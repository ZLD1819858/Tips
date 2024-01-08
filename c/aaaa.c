#include "stdio.h"
#include "IPD.h"


#define PI 3.14


struct Person {
    u32 age;
    u32 no;
};
typedef struct Person* Person;

void show_person_group(Person *arr, u32 num) {
    u32 i = 0;
    for (i = 0; i < num; i++)
    {
        printf("%u\r\n", arr[i]->no);
    }
}

const int P = 3.14;

#define INC(x) ((x) + 1)
#define ADD_STR(x)  "1_"#x

const u8 __lowest_bit_bitmap[] =
{
    /*  0 - 7  */  0,  1,  2, 27,  3, 24, 28, 32,
    /*  8 - 15 */  4, 17, 25, 31, 29, 12, 32, 14,
    /* 16 - 23 */  5,  8, 18, 32, 26, 23, 32, 16,
    /* 24 - 31 */ 30, 11, 13,  7, 32, 22, 15, 10,
    /* 32 - 36 */  6, 21,  9, 20, 19
};

i32 __rt_ffs(i32 value)
{
    return __lowest_bit_bitmap[(u32)((value & (value - 1)) ^ value) % 37];
}

i32 main(void)
{
    Person persons[2];
    struct Person p1 = {22, 0};
    struct Person p2 = {50, 1};

    persons[0] = &p1;
    persons[1] = &p2;

    struct Person *arr1[7];
    struct Person *arr2[9];
    struct Person **ptr1;
    printf("%u\r\n", sizeof persons);
    show_person_group(persons, (sizeof persons)/sizeof(void*));

    ptr1 = &arr1;
    printf("%u %u\r\n", sizeof arr1/sizeof(void*), sizeof ptr1);

    i32 iarr1[4] = {11, 12, 13, 14};
    i32 iarr2[5] = {21, 22, 23, 24, 25};
    i32 *iarr_ptr = 0U;

    iarr_ptr = iarr1;
    printf("%u, %u\r\n", sizeof iarr_ptr, sizeof iarr1);


    struct Person pp1 = {22, 0};
    struct Person pp2 = {50, 1};
    struct Person pp3 = {22, 2};
    struct Person pp4 = {50, 3};
    struct Person pp5 = {22, 4};
    struct Person pp6 = {50, 5};
    struct Person pp7 = {50, 6};

    struct Person *pp_arr1[3] = {&pp1, &pp2, &pp3};
    struct Person *pp_arr2[4] = {&pp4, &pp5, &pp6, &pp7};
    struct Person **pp_ptr = 0;

    pp_ptr = pp_arr2;
    //printf("%u, %u\r\n", ((struct Person *)((*pp_ptr)[1]))->no, 2 );
    printf("%u, %u\r\n", ((pp_ptr[3]))->no, 2 );

    INC(1 + 2);
    u8 arr[8] = ADD_STR(1);

    return 0;
}

