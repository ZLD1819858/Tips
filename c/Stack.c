#include "stdio.h"
typedef unsigned char rt_uint8_t;

rt_uint8_t stack[10];
// 动态增长的栈
typedef int STDataType;
typedef struct Stack
{
	STDataType* a;
	int top;		// 栈顶
	int capacity;  // 容量 
}Stack;
typedef struct Stack ST;

struct StaticStack
{
    rt_uint8_t* ptr;
    int top;
    int capacity;
};

void StackInit(ST* ps)
{
	ps->a = NULL;
	ps->top = ps->capacity = 0;
}
void StaticStackInit(struct StaticStack *s, rt_uint8_t *ptr, rt_uint8_t size)
{
    s->top = -1;
    s->capacity = size;
    s->ptr = ptr;
}

void StackPush(ST* ps, STDataType x)
{
	if (ps->top == ps->capacity)
	{
		int newcapacity = ps->capacity == 0 ? 4 : ps->capacity * 2;
		STDataType* tmp = (STDataType*)realloc(ps->a,newcapacity*sizeof(STDataType));
		if (tmp == NULL)
		{
			return;
		}
		ps->a = tmp;
		ps->capacity = newcapacity;
	}
	ps->a[ps->top] = x;
	ps->top++;
}
void StaticStackPush(struct StaticStack* s, rt_uint8_t value)
{
    if (s->top + 1 >= s->capacity)
    {
        printf("栈满！压栈失败！\r\n");
        return;
    }

    s->top++;
    s->ptr[s->top] = value;
}

void StackPop(ST* ps)
{
	ps->top--;
}
rt_uint8_t StaticStackPop(struct StaticStack* s)
{
    return s->ptr[(s->top)--];
}

STDataType StackTop(ST* ps)
{
	return ps->a[ps->top - 1];
}
rt_uint8_t StaticStackTop(struct StaticStack* s)
{
	return s->ptr[s->top];
}

int StackSize(ST* ps)
{
	return ps->top;
}
rt_uint8_t StaticStackSize(struct StaticStack* s) {
	return s->top + 1;
}

int StackEmpty(ST* ps)
{
	return ps->top == 0;
}
int StaticStackEmpty(struct StaticStack* s)
{
	return s->top == -1;
}
void StackDestroy(ST* ps)
{
	free(ps->a);
	ps->a = NULL;
	ps->top = ps->capacity = 0;
}


int main()
{
    /* Static Stack */
    rt_uint8_t staticstack1[10];
    struct StaticStack stack2;
    StaticStackInit(&stack2, staticstack1, sizeof(staticstack1));
    /*
    StaticStackPush(&stack2, 1);
    StaticStackPush(&stack2, 2);
    StaticStackPush(&stack2, 3);
    StaticStackPush(&stack2, 4);
    StaticStackPush(&stack2, 5);
    StaticStackPush(&stack2, 6);
    StaticStackPush(&stack2, 7);
    StaticStackPush(&stack2, 8);
    StaticStackPush(&stack2, 9);
    StaticStackPush(&stack2, 10);
    StaticStackPush(&stack2, 11);
    StaticStackPush(&stack2, 12);
    */

    //int b1 = StaticStackPop(&stack2);
    //int b2 = StaticStackPop(&stack2);
    //printf("%d %d\r\n", b1, b2);

    int a = StaticStackEmpty(&stack2);

    unsigned char arr[5][12];

    printf("%d %d\r\n", a, sizeof(arr[1]));

    unsigned int a2 = 0xFFFFFFFF / 100 - 2000;
    unsigned int a3 = 20000;

    unsigned int a4 = (0xFFFFFFFF / 100) - a2 + a3;

    printf("%u %u\r\n", a3 - a2, a4);


    return 0;
}
