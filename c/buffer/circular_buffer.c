#include "circular_buffer.h"

int push(circular_buffer *cb, int data)
{
    if (SIZE > cb->count)
    {
        cb->buffer[cb->head] = data;
        cb->head = (cb->head + 1) % SIZE;
        cb->count++;
        return 0;
    }

    return -1;
}

int pop(circular_buffer *cb, int *data)
{
    if (0 < cb->count)
    {
        *data = cb->buffer[cb->tail];
        cb->tail = (cb->tail + 1) % SIZE;
        cb->count--;
        return 0;
    }

    return -1;
}
