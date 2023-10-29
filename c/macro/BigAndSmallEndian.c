#include <stdio.h>

// 共用体中很重要的一点：a和b都是从u1的低地址开始存放的。
// 假设u1所在的4字节地址分别是：0、1、2、3的话，那么a自然就是0、1、2、3；
// b所在的地址是0而不是3.

union myunion
{
	int a;
	char b;
};

// 如果是小端模式则返回1，大端模式则返回0
int is_little_endian(void)
{
	union myunion u1;
	u1.a = 0x12345678;				// 地址0的那个字节内是0x78（小端）或者0x12（大端）
    if(0x78 == u1.b)
        return 1;
    else if(0x12 == u1.b)
	    return 0;
}

int is_little_endian2(void)
{
	int a = 0x12345678;
	char b = *((char *)(&a));		// 指针方式其实就是共用体的本质
	if(0x78 == b)
        return 1;
    else if(0x12 == b)
	    return 0;
}

int main(void)
{
	int i = is_little_endian2();
	// int i = is_little_endian();
	if (i == 1)
	{
		printf("小端模式\n");
	}
	else
	{
		printf("大端模式\n");
	}
    int a = 0x12345678;
    char *a1 = ((char *)(&a));
    char *a2 = (((char *)&a)+1);
    int index = 0;
    for (index = 0; index < 6;index++) {
        printf("Addr:%p Value:%x\n", a1+index, *(a1+index));
    }

    return 0;
}



