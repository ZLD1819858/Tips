#ifndef __LLIST_H_
#define __LLIST_H_

#include "IPD.h"

struct LListNode {
    struct LListNode *next;
    struct LListNode *prev;
};
typedef struct LListNode LListNode;
typedef struct LListNode *LListNodeRef;

static inline void LListInit(LListNodeRef node) {
    node->next = node;
    node->prev = node;
}

static inline void LListInsertAfter(LListNodeRef head, LListNodeRef node) {
    head->next->prev    = node;
    node->next          = head->next;

    head->next          = node;
    node->prev          = head;
}
static inline void LListInsertBefore(LListNodeRef head, LListNodeRef node) {
    head->prev->next    = node;
    node->prev          = head->prev;

    head->prev          = node;
    node->next          = head;
}
static inline void LListRemove(LListNodeRef node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;

    node->next = node;
    node->prev = node;
}
static inline u8 LListIsEmpry(LListNodeRef node) {
    return node->next == node;
}
static inline u32 LListLength(LListNodeRef head) {
    u32 len = 0;
    LListNodeRef node = head;
    while(node->next != head) {
        node = node->next;
        len++;
    }
    return len;
}

#define LListIterator(cursor, head) \
    for((cursor) = (head)->next; cursor != (head); (cursor) = (cursor)->next)


#endif /* __LLIST_H_ */
