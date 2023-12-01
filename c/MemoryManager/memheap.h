#ifndef __MEMHEAP_H_
#define __MEMHEAP_H_

#include "../inc/IPD.h"
#include "../inc/llist.h"

struct Object
{
    char        name[32];                       /**< name of kernel object */
    u8          type;                                    /**< type of kernel object */
    u8          flag;                                    /**< flag of kernel object */
    /*[RTSECA_SWREQ_0012]*/
#ifdef RT_USING_OSA
    int       osa_ref_count;                            /**< ref count for osa */
#endif

    LListNode   list;                                    /**< list node of kernel object */
};
typedef struct Object   Object;                     /**< Type for kernel objects. */
typedef struct Object   *ObjectRef;                  /**< Type for kernel objects. */


typedef struct Memheap Memheap;
typedef struct Memheap *MemheapRef;
typedef struct MemheapItem  MemheapItem;
typedef struct MemheapItem  *MemheapItemRef;

struct MemheapItem
{
    u32                 magic;                      /**< magic number for memheap */
    MemheapRef          pool_ptr;                   /**< point of pool */

    MemheapItemRef      next;                       /**< next memheap item */
    MemheapItemRef      prev;                       /**< prev memheap item */

    MemheapItemRef      next_free;                  /**< next free memheap item */
    MemheapItemRef      prev_free;                  /**< prev free memheap item */
#ifdef RT_USING_MEMTRACE
    u8              owner_thread_name[4];       /**< owner thread name */
#endif /* RT_USING_MEMTRACE */
};

/**
 * Base structure of memory heap object
 */
struct Memheap
{
    Object              parent;                     /**< inherit from rt_object */
    void                *start_addr;                 /**< pool start address and size */

    usize               pool_size;                  /**< pool size */
    usize               available_size;             /**< available size */
    usize               max_used_size;              /**< maximum allocated size */

    MemheapItemRef      block_list;                 /**< used block list */
    MemheapItemRef      free_list;                  /**< free block list */
    MemheapItem         free_header;                /**< free block list header */
};

#endif /* __MEMHEAP_H_ */
