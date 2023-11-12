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
    head->next->prev    = node;
    node->next          = head->next;

    head->next          = node;
    node->prev          = head;
}

#endif /* __LLIST_H_ */
