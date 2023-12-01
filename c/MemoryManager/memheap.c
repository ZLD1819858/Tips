#include "stdio.h"
#include "errno.h"
#include "memheap.h"
#include "../inc/IPD.h"
#include "../inc/llist.h"
#include "string.h"
#include "stdint.h"

/* dynamic pool magic and mask */
#define RT_MEMHEAP_MAGIC        0x1ea01ea0
#define RT_MEMHEAP_MASK         0xFFFFFFFE
#define RT_MEMHEAP_USED         0x01
#define RT_MEMHEAP_FREED        0x00

#define RT_MEMHEAP_IS_USED(i)   ((i)->magic & RT_MEMHEAP_USED)
#define RT_MEMHEAP_MINIALLOC    12

#define RT_MEMHEAP_SIZE         ALIGN_UP_AS(sizeof(MemheapItem), 4)
#define MEMITEM_SIZE(item)      ((u64)item->next - (u64)item - RT_MEMHEAP_SIZE)
#define MEMITEM(ptr)            (MemheapItemRef)((u8*)ptr - RT_MEMHEAP_SIZE)



void rt_memheap_free(void *ptr);

static inline void _remove_next_ptr(MemheapItemRef next_ptr)
{
    /* Fix the crash problem after opening Oz optimization on ac6  */
    /* Fix IAR compiler warning  */
    next_ptr->next_free->prev_free = next_ptr->prev_free;
    next_ptr->prev_free->next_free = next_ptr->next_free;
    next_ptr->next->prev = next_ptr->prev;
    next_ptr->prev->next = next_ptr->next;
}

u32 MemheapInit(MemheapRef memheap,
                         const char        *name,
                         void              *start_addr,
                         usize         size)
{
    MemheapItemRef item = 0;
    u32 ret = 0;

    /* parameter check */
    if (ALIGN_DOWN_AS(size, 4) >= (2 * RT_MEMHEAP_SIZE))
    {
        start_addr = (void *)ALIGN_UP_AS((uintptr_t)start_addr, 4);

        memheap->start_addr     = start_addr;
        memheap->pool_size      = ALIGN_DOWN_AS(size, 4);   // BUG?
        memheap->available_size = memheap->pool_size - (2 * RT_MEMHEAP_SIZE); // 这里为什么需要减去2个MEMHEAP_ITEM的大小
        memheap->max_used_size  = memheap->pool_size - memheap->available_size; // 最大使用的大小
        /* initialize the free list header */
        item            = &(memheap->free_header);
        item->magic     = (RT_MEMHEAP_MAGIC | RT_MEMHEAP_FREED);    // 标记空闲内存块
        item->pool_ptr  = memheap;
        item->next      = 0;
        item->prev      = 0;
        item->next_free = item;             // 空闲内存块双向链表
        item->prev_free = item;             // 空闲内存块双向链表

        /* set the free list to free list header */
        memheap->free_list = item;          // 把空闲内存块记录在空闲链表中

        /* initialize the first big memory block */
        item            = (MemheapItemRef)start_addr;
        item->magic     = (RT_MEMHEAP_MAGIC | RT_MEMHEAP_FREED);

        item->pool_ptr  = memheap;
        item->next      = 0;
        item->prev      = 0;
        item->next_free = item;
        item->prev_free = item;

#ifdef RT_USING_MEMTRACE
        rt_memset(item->owner_thread_name, ' ', sizeof(item->owner_thread_name));
#endif /* RT_USING_MEMTRACE */

        item->next = (MemheapItemRef)
                    ((u8 *)item + memheap->available_size + RT_MEMHEAP_SIZE);
        item->prev = item->next;

        /* block list header */
        memheap->block_list = item;

        /* place the big memory block to free list */
        item->next_free = memheap->free_list->next_free;
        item->prev_free = memheap->free_list;
        memheap->free_list->next_free->prev_free = item;
        memheap->free_list->next_free            = item;

        /* move to the end of memory pool to build a small tailer block,
        * which prevents block merging
        */
        item = item->next;
        /* it's a used memory block */
        item->magic     = (RT_MEMHEAP_MAGIC | RT_MEMHEAP_USED);
        item->pool_ptr  = memheap;
        item->next      = (MemheapItemRef)start_addr;
        item->prev      = (MemheapItemRef)start_addr;
        /* not in free list */
        item->next_free = item->prev_free = 0;
    }
    else
    {
        ret = -1;
    }

    return ret;
}

static inline MemheapItemRef rt_memheap_find(MemheapRef heap, const usize size)
{
    MemheapItemRef header_ptr = 0;
    u32 free_size = 0;

    header_ptr = heap->free_list->next_free;
    while ((header_ptr != heap->free_list) && (free_size < size))
    {
        /* get current freed memory block size */
        free_size = MEMITEM_SIZE(header_ptr);
        if (free_size < size)
        {
            /* move to next free memory block */
            header_ptr = header_ptr->next_free;
        }
    }

    if (free_size < size)
    {
        header_ptr = 0;
    }

    return header_ptr;
}

static inline void rt_memheap_split(MemheapRef heap, MemheapItemRef header_ptr,
    const usize size)
{
    MemheapItemRef new_ptr = 0;

    /* split the block. */
    new_ptr = (MemheapItemRef)(((u8 *)header_ptr) + size + RT_MEMHEAP_SIZE);

    /* mark the new block as a memory block and freed. */
    new_ptr->magic         = (RT_MEMHEAP_MAGIC | RT_MEMHEAP_FREED);

    /* put the pool pointer into the new block. */
    new_ptr->pool_ptr      = heap;

#ifdef RT_USING_MEMTRACE
    rt_memset(new_ptr->owner_thread_name, ' ', sizeof(new_ptr->owner_thread_name));
#endif /* RT_USING_MEMTRACE */

    /* break down the block list */
    new_ptr->prev          = header_ptr;
    new_ptr->next          = header_ptr->next;

    header_ptr->next->prev = new_ptr;
    header_ptr->next       = new_ptr;

    /* remove header_ptr from free list */
    header_ptr->next_free->prev_free = header_ptr->prev_free;
    header_ptr->prev_free->next_free = header_ptr->next_free;
    header_ptr->next_free  = 0;
    header_ptr->prev_free  = 0;

    /* insert new_ptr to free list */
    new_ptr->next_free     = heap->free_list->next_free;
    new_ptr->prev_free     = heap->free_list;
    heap->free_list->next_free->prev_free = new_ptr;
    heap->free_list->next_free            = new_ptr;

    /* decrement the available byte count.  */
    heap->available_size = heap->available_size - size - RT_MEMHEAP_SIZE;
    if ((heap->pool_size - heap->available_size) > (heap->max_used_size))
    {
        heap->max_used_size = heap->pool_size - heap->available_size;
    }
}

static inline void rt_memheap_new(MemheapRef heap, MemheapItemRef header_ptr,
    const usize free_size)
{
    /* decrement the entire free size from the available bytes count. */
    heap->available_size = heap->available_size - free_size;
    if ((heap->pool_size - heap->available_size) > (heap->max_used_size))
    {
        heap->max_used_size = heap->pool_size - heap->available_size;
    }

    /* remove header_ptr from free list */

    header_ptr->next_free->prev_free = header_ptr->prev_free;
    header_ptr->prev_free->next_free = header_ptr->next_free;
    header_ptr->next_free = 0;
    header_ptr->prev_free = 0;
}

static inline void *_alloc(MemheapRef heap, MemheapItemRef header_ptr, usize size)
{
    const u32 free_size = MEMITEM_SIZE(header_ptr);

    /* determine if the block needs to be split. */
    if (free_size >= (size + RT_MEMHEAP_SIZE + RT_MEMHEAP_MINIALLOC))
    {
        rt_memheap_split(heap, header_ptr, size);
    }
    else
    {
        rt_memheap_new(heap, header_ptr, free_size);
    }

    /* Mark the allocated block as not available. */
    header_ptr->magic = (RT_MEMHEAP_MAGIC | RT_MEMHEAP_USED);

    /* Return a memory address to the caller.  */

    return (void *)((u8 *)header_ptr + RT_MEMHEAP_SIZE);
}

void *rt_memheap_alloc(MemheapRef heap, usize size)
{
    void *new_mem = 0;
    MemheapItemRef header_ptr = 0;

    if (heap != 0)
    {
        /* align allocated size */
        size = ALIGN_UP_AS(size, 4);
        if (size < RT_MEMHEAP_MINIALLOC)
        {
            size = RT_MEMHEAP_MINIALLOC;
        }
        if (size <= heap->available_size)
        {
            /* search on free list */
            /* get the first free memory block */
            header_ptr = rt_memheap_find(heap, size);
            if (header_ptr != 0)
            {
                new_mem = _alloc(heap, header_ptr, size);
            }
            else
            {
            }
        }
        else
        {
        }
    }

    return new_mem;
}
static inline void rt_memheap_combine(MemheapRef heap, usize oldsize, usize newsize,
        void *ptr, MemheapItemRef header_ptr, MemheapItemRef next_ptr)
{
    /* decrement the entire free size from the available bytes count. */
    heap->available_size = heap->available_size - (newsize - oldsize);
    if ((heap->pool_size - heap->available_size) > heap->max_used_size)
    {
        heap->max_used_size = heap->pool_size - heap->available_size;
    }

    /* remove next_ptr from free list */

    _remove_next_ptr(next_ptr);

    /* build a new one on the right place */
    next_ptr = (MemheapItemRef)((char *)ptr + newsize);


    /* mark the new block as a memory block and freed. */
    next_ptr->magic = (RT_MEMHEAP_MAGIC | RT_MEMHEAP_FREED);

    /* put the pool pointer into the new block. */
    next_ptr->pool_ptr = heap;

#ifdef RT_USING_MEMTRACE
    rt_memset((void *)next_ptr->owner_thread_name, ' ', sizeof(next_ptr->owner_thread_name));
#endif /* RT_USING_MEMTRACE */

    next_ptr->prev         = header_ptr;
    next_ptr->next         = header_ptr->next;
    header_ptr->next->prev = next_ptr;
    header_ptr->next       = next_ptr;

    /* insert next_ptr to free list */
    next_ptr->next_free = heap->free_list->next_free;
    next_ptr->prev_free = heap->free_list;
    heap->free_list->next_free->prev_free = next_ptr;
    heap->free_list->next_free            = next_ptr;
}

static inline void *rt_memheap_expand(MemheapRef heap, void *ptr, usize oldsize, usize newsize)
{
    MemheapItemRef header_ptr = (MemheapItemRef)((u8 *)ptr - RT_MEMHEAP_SIZE);
    void *new_mem = 0;
    void *new_ptr = 0;

    MemheapItemRef next_ptr = 0;

    next_ptr = header_ptr->next;

    /* header_ptr should not be the tail */
    if (next_ptr > header_ptr)
    {
        /* check whether the following free space is enough to expand */
        if ((RT_MEMHEAP_IS_USED(next_ptr) != TRUE) && \
            ((MEMITEM_SIZE(next_ptr) + oldsize) > (newsize + RT_MEMHEAP_MINIALLOC)))
        {
            /* Here is the ASCII art of the situation that we can make use of
                * the next free node without alloc/memcpy, |*| is the control
                * block:
                *
                *      oldsize           free node
                * |*|-----------|*|----------------------|*|
                *         newsize          >= minialloc
                * |*|----------------|*|-----------------|*|
                */
            rt_memheap_combine(heap, oldsize, newsize, ptr, header_ptr, next_ptr);
            new_mem = ptr;
        }
        else
        {
            /* re-allocate a memory block */
            new_ptr = (void *)rt_memheap_alloc(heap, newsize);
            if (new_ptr != 0)
            {
                memcpy(new_ptr, ptr, oldsize < newsize ? oldsize : newsize);
                rt_memheap_free(ptr);
                new_mem = new_ptr;
            }
        }
    }

    return new_mem;
}

static inline void *rt_memheap_shrink(MemheapRef heap, void *ptr, usize oldsize, usize newsize)
{
    MemheapItemRef header_ptr = (MemheapItemRef)((u8 *)ptr - RT_MEMHEAP_SIZE);
    MemheapItemRef new_ptr = 0;
    MemheapItemRef free_ptr = 0;
    void* new_mem = 0;

    /* split the block. */
    new_ptr = (MemheapItemRef)(((u8 *)header_ptr) + newsize + RT_MEMHEAP_SIZE);

    /* mark the new block as a memory block and freed. */
    new_ptr->magic = (RT_MEMHEAP_MAGIC | RT_MEMHEAP_FREED);
    /* put the pool pointer into the new block. */
    new_ptr->pool_ptr = heap;

#ifdef RT_USING_MEMTRACE
    rt_memset(new_ptr->owner_thread_name, ' ', sizeof(new_ptr->owner_thread_name));
#endif /* RT_USING_MEMTRACE */

    /* break down the block list */
    new_ptr->prev          = header_ptr;
    new_ptr->next          = header_ptr->next;
    header_ptr->next->prev = new_ptr;
    header_ptr->next       = new_ptr;

    /* determine if the block can be merged with the next neighbor. */
    if (RT_MEMHEAP_IS_USED(new_ptr->next) != TRUE)
    {
        /* merge block with next neighbor. */
        free_ptr = new_ptr->next;
        heap->available_size = heap->available_size - MEMITEM_SIZE(free_ptr);


        free_ptr->next->prev = new_ptr;
        new_ptr->next   = free_ptr->next;

        /* remove free ptr from free list */
        free_ptr->next_free->prev_free = free_ptr->prev_free;
        free_ptr->prev_free->next_free = free_ptr->next_free;
    }

    /* insert the split block to free list */
    new_ptr->next_free = heap->free_list->next_free;
    new_ptr->prev_free = heap->free_list;
    heap->free_list->next_free->prev_free = new_ptr;
    heap->free_list->next_free            = new_ptr;

    /* increment the available byte count.  */
    heap->available_size = heap->available_size + MEMITEM_SIZE(new_ptr);

    /* return the old memory block */
    new_mem = ptr;

    return new_mem;
}

/**
 * @brief This function will change the size of previously allocated memory block.
 *
 * @param heap is a pointer to the memheap object, which will reallocate
 *             memory from the block
 *
 * @param ptr is a pointer to start address of memory.
 *
 * @param newsize is the required new size.
 *
 * @return the changed memory block address.
 */
void *rt_memheap_realloc(MemheapRef heap, void *ptr, usize newsize)
{
    void* new_mem = 0;
    MemheapItemRef header_ptr = 0;
    usize oldsize = 0;

    if (heap != 0)
    {
        if (newsize != 0)
        {
            /* align allocated size */
            newsize = ALIGN_UP_AS(newsize, 4);
            if (newsize < RT_MEMHEAP_MINIALLOC)
            {
                newsize = RT_MEMHEAP_MINIALLOC;
            }

            if (ptr != 0)
            {
                /* get memory block header and get the size of memory block */
                header_ptr = (MemheapItemRef)((u8 *)ptr - RT_MEMHEAP_SIZE);
                oldsize = MEMITEM_SIZE(header_ptr);

                /* re-allocate memory */
                if (newsize <= oldsize)
                {
                    /* don't split when there is less than one node space left */
                    if (newsize + RT_MEMHEAP_SIZE + RT_MEMHEAP_MINIALLOC >= oldsize)
                    {
                        new_mem = ptr;
                    }
                    else
                    {
                        new_mem = rt_memheap_shrink(heap, ptr, oldsize, newsize);
                    }

                }
                else
                {
                    new_mem = rt_memheap_expand(heap, ptr, oldsize, newsize);
                }
            }
            else
            {
                new_mem = rt_memheap_alloc(heap, newsize);
            }
        }
        else
        {
            rt_memheap_free(ptr);
        }
    }

    return new_mem;
}

static inline void _free(MemheapRef heap, MemheapItemRef header_ptr, void *ptr)
{
    MemheapItemRef new_ptr = 0;
    MemheapItemRef n = 0;
    u32 insert_header = 1;
#if defined(RT_MEMHEAP_BSET_MODE)
    rt_uint32_t blk_size = 0;
#endif

    /* Mark the memory as available. */
    header_ptr->magic = (RT_MEMHEAP_MAGIC | RT_MEMHEAP_FREED);
    /* Adjust the available number of bytes. */
    heap->available_size += MEMITEM_SIZE(header_ptr);

    /* Determine if the block can be merged with the previous neighbor. */
    if (RT_MEMHEAP_IS_USED(header_ptr->prev) != TRUE)
    {

        /* adjust the available number of bytes. */
        heap->available_size += RT_MEMHEAP_SIZE;

        /* yes, merge block with previous neighbor. */
        (header_ptr->prev)->next = header_ptr->next;
        (header_ptr->next)->prev = header_ptr->prev;

        /* move header pointer to previous. */
        header_ptr = header_ptr->prev;
        /* don't insert header to free list */
        insert_header = 0;
    }

    /* determine if the block can be merged with the next neighbor. */
    if (RT_MEMHEAP_IS_USED(header_ptr->next) != TRUE)
    {
        /* adjust the available number of bytes. */
        heap->available_size += RT_MEMHEAP_SIZE;

        /* merge block with next neighbor. */
        new_ptr = header_ptr->next;


        new_ptr->next->prev = header_ptr;
        header_ptr->next    = new_ptr->next;

        /* remove new ptr from free list */
        new_ptr->next_free->prev_free = new_ptr->prev_free;
        new_ptr->prev_free->next_free = new_ptr->next_free;
    }

    if (insert_header == 1)
    {
        n = heap->free_list->next_free;;
#if defined(RT_MEMHEAP_BSET_MODE)
        blk_size = MEMITEM_SIZE(header_ptr);
        for (;n != heap->free_list; n = n->next_free)
        {
            rt_uint32_t m = MEMITEM_SIZE(n);
            if (blk_size <= m)
            {
                break;
            }
        }
#endif
        /* no left merge, insert to free list */
        header_ptr->next_free = n;
        header_ptr->prev_free = n->prev_free;
        n->prev_free->next_free = header_ptr;
        n->prev_free = header_ptr;

    }
#ifdef RT_USING_MEMTRACE
    rt_memset(header_ptr->owner_thread_name, ' ', sizeof(header_ptr->owner_thread_name));
#endif /* RT_USING_MEMTRACE */
}

/**
 * @brief This function will release the allocated memory block by
 *        rt_malloc. The released memory block is taken back to system heap.
 *
 * @param ptr the address of memory which will be released.
 */
void rt_memheap_free(void *ptr)
{
    MemheapRef      heap = 0;
    MemheapItemRef  header_ptr = 0;

    /* NULL check */
    if (ptr != 0)
    {
        /* set initial status as OK */
        header_ptr = (MemheapItemRef)((u8 *)ptr - RT_MEMHEAP_SIZE);


        /* check magic */
        if ((header_ptr->magic == (RT_MEMHEAP_MAGIC | RT_MEMHEAP_USED)) && \
        /* check whether this block of memory has been over-written. */
            ((header_ptr->next->magic & RT_MEMHEAP_MASK) == RT_MEMHEAP_MAGIC))
        {
            /* get pool ptr */
            heap = header_ptr->pool_ptr;
            if (heap != 0)
            {
                _free(heap, header_ptr, ptr);
            }
        }
    }
}

/**
* @brief This function will caculate the total memory, the used memory, and
*        the max used memory.
*
* @param heap is a pointer to the memheap object, which will reallocate
*             memory from the block
*
* @param total is a pointer to get the total size of the memory.
*
* @param used is a pointer to get the size of memory used.
*
* @param max_used is a pointer to get the maximum memory used.
*/
void rt_memheap_info(MemheapRef heap,
                     usize *total,
                     usize *used,
                     usize *max_used)
{
    if (heap != 0)
    {
        if (total != 0)
        {
            *total = heap->pool_size;
        }

        if (used != 0)
        {
            *used = heap->pool_size - heap->available_size;
        }

        if (max_used != 0)
        {
            *max_used = heap->max_used_size;
        }
    }
}


Memheap heap;
u8 ATTR_ALIGN(4) buffer[4096] = {0};

void func() {
    int i, j;
    for (i = 0; i < 1000000; i++) {
        j = i; // 占位操作，以产生可测量的执行时间
    }
}

int main(int argc, char **argv) {
    /*
    printf("%lu Bits Compiler.\n", sizeof(void*) * 8);
    printf("Memheap Size:\t\t%d\n", sizeof(Memheap));
    printf("MemheapItem Size: \t%d\n", sizeof(MemheapItem));
    MemheapInit(&heap, "aaa", &buffer[0], 4096);
    void *ptrA0 = rt_memheap_alloc(&heap, 32);
    printf("Alloc Memory Addr: 0x%X\n", ptrA0);
    void *ptrA1 = rt_memheap_alloc(&heap, 32);
    printf("Alloc Memory Addr: 0x%X\n", ptrA1);
    void *ptrA2 = rt_memheap_alloc(&heap, 32);
    printf("Alloc Memory Addr: 0x%X\n", ptrA2);
    */


    int i = 0;
    while(i < 100000000)
    {

    func();
    i++;
    }

    return 0;
}

