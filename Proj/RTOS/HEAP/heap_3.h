
#ifndef __HEAP_3_H
#define __HEAP_3_H

#include "std_types.h"
#include "stdlib.h"


#define HEAP_3_USE_C_IMPLEMENTATION
#ifdef HEAP_3_USE_C_IMPLEMENTATION

void *pvPortMalloc(uint32_t size);
void *pvPortCalloc(uint32_t n, uint32_t size);
void vPortFree(void *ptr);

#else


#define pvPortMalloc(__size_) malloc(__size_)
#define pvPortCalloc(__n_,__size_) calloc(__n_,__size_)
#define vPortFree(ptr) free(ptr)

#endif //HEAP_3_USE_C_IMPLEMENTATION


#endif //__HEAP_3_H
