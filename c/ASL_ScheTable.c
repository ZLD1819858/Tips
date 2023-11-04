#include "stdio.h"
#include "IPD.h"

struct Task
{
    u32     id;
    char    name[32];
};
typedef struct Task Task;
typedef struct Task *TaskRef;



typedef void (*app_alarm_cb)(void);

struct Application
{
    TaskRef     taskList;
    u32         taskSum;
    app_alarm_cb start_cb;
    app_alarm_cb stop_cb;
};


typedef struct Application Application;
typedef struct Application *ApplicationRef;

Task taskList0[2] =
{
    {
        .id = 0,
        .name = "Task0"
    },
    {
        .id = 1,
        .name = "Task1"
    }
};

Task taskList1[3] =
{
    {
        .id = 2,
        .name = "Task2"
    },
    {
        .id = 3,
        .name = "Task3"
    },
    {
        .id = 4,
        .name = "Task4"
    },
};

void App1_AlarmStart(void) {
    printf("alarm 1 start\n");
}

void App1_AlarmStop(void) {
    printf("alarm 1 stop\n");
}



void App2_AlarmStart(void) {
    printf("alarm 2 start\n");
}
void App2_AlarmStop(void) {
    printf("alarm 2 stop\n");
}

Application appList[2] =
{
    {
        .taskList   =   taskList0,
        .taskSum    =   sizeof(taskList0)/sizeof(Task),
        .start_cb   =   App1_AlarmStart,
        .stop_cb    =   App1_AlarmStop,

    },
    {
        .taskList   =   taskList1,
        .taskSum    =   sizeof(taskList1)/sizeof(Task),
        .start_cb   =   App2_AlarmStart,
        .stop_cb    =   App2_AlarmStop,
    },
};

void StartupScheTable(u32 scheTableId)
{
    u32 taskSum = appList[scheTableId].taskSum;
    int i = 0;
    for (i = 0; i < taskSum; i++) {
        printf("%s\n", appList[scheTableId].taskList[i].name);
    }

    appList[scheTableId].start_cb();
    appList[scheTableId].stop_cb();
}



int main(int argc, char **argv)
{
    StartupScheTable(1);
    StartupScheTable(0);

}
