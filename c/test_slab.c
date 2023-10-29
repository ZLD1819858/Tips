#include <stdio.h>

int zoneindex(int *bytes)
{
    int n = (int)(*bytes);

    if (n < 128)
    {
        *bytes = n = (n + 7) & ~7;
        /* 8 byte chunks, 16 zones */
        return (n / 8 - 1);
    }
    if (n < 256)
    {
        *bytes = n = (n + 15) & ~15;
        return (n / 16 + 7);
    }
    if (n < 8192)
    {
        if (n < 512)
        {
            *bytes = n = (n + 31) & ~31;
            return (n / 32 + 15);
        }
        if (n < 1024)
        {
            *bytes = n = (n + 63) & ~63;
            return (n / 64 + 23);
        }
        if (n < 2048)
        {
            *bytes = n = (n + 127) & ~127;
            return (n / 128 + 31);
        }
        if (n < 4096)
        {
            *bytes = n = (n + 255) & ~255;
            return (n / 256 + 39);
        }
        *bytes = n = (n + 511) & ~511;
        return (n / 512 + 47);
    }
    if (n < 16384)
    {
        *bytes = n = (n + 1023) & ~1023;
        return (n / 1024 + 55);
    }
    printf("Unexpected byte count %d", n);
    return 0;
}

int main(void)
{
    int i = 214746;
    printf("输入数字:");
    scanf("%d",&i);
    
    int result = zoneindex(&i);

    // printf("%d,%d",sizeof(int),sizeof(long));

    printf("%d\n",result);

    

    return 0;
}