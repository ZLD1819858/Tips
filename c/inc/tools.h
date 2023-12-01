#ifndef __TOOLS_H_
#define __TOOLS_H_

#include "IPD.h"
#include "stdint.h"

LOCAL_INLINE u8 isAligned(void *ptr, usize n) {
    return ((uintptr_t)(ptr) % n) == 0;
}

#endif /* __TOOLS_H_ */
