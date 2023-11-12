#ifndef __MEMHEAP_H_
#define __MEMHEAP_H_

#include "IPD.h"

struct object
{
    char        name[32];                       /**< name of kernel object */
    u8          type;                                    /**< type of kernel object */
    u8          flag;                                    /**< flag of kernel object */
    /*[RTSECA_SWREQ_0012]*/
#ifdef RT_USING_OSA
    int       osa_ref_count;                            /**< ref count for osa */
#endif

    rt_list_t  list;                                    /**< list node of kernel object */
};
typedef struct rt_object *rt_object_t;                  /**< Type for kernel objects. */

struct rt_memheap_item
{
    u32                     magic;                      /**< magic number for memheap */
    struct rt_memheap       *pool_ptr;                   /**< point of pool */

    struct rt_memheap_item *next;                       /**< next memheap item */
    struct rt_memheap_item *prev;                       /**< prev memheap item */

    struct rt_memheap_item *next_free;                  /**< next free memheap item */
    struct rt_memheap_item *prev_free;                  /**< prev free memheap item */
#ifdef RT_USING_MEMTRACE
    u8              owner_thread_name[4];       /**< owner thread name */
#endif /* RT_USING_MEMTRACE */
};

/**
 * Base structure of memory heap object
 */
struct rt_memheap
{
    struct object        parent;                     /**< inherit from rt_object */

    void                    *start_addr;                 /**< pool start address and size */

    usize                   pool_size;                  /**< pool size */
    usize                   available_size;             /**< available size */
    usize                   max_used_size;              /**< maximum allocated size */

    struct rt_memheap_item *block_list;                 /**< used block list */

    struct rt_memheap_item *free_list;                  /**< free block list */
    struct rt_memheap_item  free_header;                /**< free block list header */
};

#endif /* __MEMHEAP_H_ */
