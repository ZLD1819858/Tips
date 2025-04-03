#ifndef __CIRCULAR_BUFFER_H__
#define __CIRCULAR_BUFFER_H__

typedef struct {
    int buffer[SIZE];
    int head;
    int tail;
    int count;
} circular_buffer;


#endif /* __CIRCULAR_BUFFER_H__ */

