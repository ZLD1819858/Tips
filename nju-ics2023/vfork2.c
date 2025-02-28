/* vfork() */
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int main (void)
{
    int count = 1; 
    int child;
    printf("Before create son, the father's count is:%d\n", count);   /*创建进程之前*/
    if(!(child = vfork())) {  
        /*这里是子进程执行区*/
        int i;
        for(i = 0; i < 100; i++) {
            printf("This is son, The i is: %d\n", i);
            if(i == 70) {
                exit(1);
            }
        }
        printf("This is son, his pid is: %d and the count is: %d\n", getpid(), ++count);
        exit(1);  
        /*子进程退出*/
    } else {  
        /*父进程执行区*/
        printf("After son, This is father, his pid is: %d and the count is: %d, and the child is: %d\n", getpid(), count, child); 
    }
    
    return 0;
}



