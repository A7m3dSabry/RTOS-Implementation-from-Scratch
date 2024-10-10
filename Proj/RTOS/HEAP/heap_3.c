#include "heap_3.h"


#include "std_types.h"
#ifdef HEAP_3_USE_C_IMPLEMENTATION


void *pvPortMalloc(uint32_t size){
    return malloc(size);
}

void *pvPortCalloc(uint32_t n, uint32_t size){
    return calloc(n,size);
}

void vPortFree(void *ptr){
    free(ptr);
}

#endif
