#ifndef NEW_H
#define NEW_H

#include <stdlib.h>

extern void* pvPortMalloc(size_t xWantedSize);
extern void vPortFree(void* pv);

/*
void* malloc(size_t size) {
    return pvPortMalloc(size);
}

void* calloc(size_t num, size_t size) {
    return pvPortMalloc(num * size);
}

void free(void* ptr) {
    return vPortFree(ptr);
}
*/

void* operator new(size_t sz) {
    return pvPortMalloc(sz);
}

void* operator new[](size_t sz) {
    return pvPortMalloc(sz);
}

void operator delete(void* p) {
    vPortFree(p);
}

void operator delete[](void* p) {
    vPortFree(p);
}

#endif  // NEW_H
