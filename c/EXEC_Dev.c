#include "stdio.h"
#include "time.h"
#include "unistd.h"
#include "IPD.h"

/* 周期任务开发 */


typedef struct {
    u32 group_no[2];        // 0:存储核上组总数，1:当前运行组索引
    void *cur_group_ptr;
    u32 group[];
}rt_cpu_exec_group;

unsigned int arr1_1[4] = {1,2,3,4};
unsigned int arr1_2[8] = {5,6,7,8,9,10,11,12};
unsigned int arr1_3[7] = {13,14,15,16,17,18,19};
unsigned int *arr1[3] = {arr1_1, arr1_2, arr1_3};

unsigned int arr2_1[4] = {101,102,103,104};
unsigned int arr2_2[8] = {105,106,107,108,109,1010,1011,1012};
unsigned int arr2_3[7] = {33,34,35,36,37,38,39};
unsigned int arr2_4[2] = {40,41,42,43,44,45,46};
unsigned int *arr2[4] = {arr2_1, arr2_2, arr2_3, arr2_4};

unsigned int **all_arr[2] = {arr1, arr2};
/* all_arr[0][2][3]？ */

int main(void) {

    unsigned int *temp = all_arr[0][0];
    printf("%u %u %u\n", sizeof(all_arr[0][1]), sizeof(temp), all_arr[0][0] == arr1_1?1:0);
    printf("%u\n", all_arr[1][1][3]);
    time_t currentTime = time(NULL);  // 获取当前系统时间
    printf("%llu\n",currentTime);
    struct tm *localTime = localtime(&currentTime);  // 转换为本地时间

    // 使用 strftime 函数格式化时间为字符串
    char timeString[50];
    strftime(timeString, sizeof(timeString), "%Y-%m-%d %H:%M:%S", localTime);

    printf("当前时间：%s\n", timeString);
    /*
    while(1) {
        time_t tick = time(NULL);
        while(tick + 1 > time(NULL));
        //msleep(500);

        printf("go..\n");
    }
    */
    return 0;
}