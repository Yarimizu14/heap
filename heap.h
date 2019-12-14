#ifndef _HEAP
#define _HEAP

#include "stddef.h"

const int HEAP_SIZE = 50;
const int ROOT_INDEX = 1;

typedef struct heap_ {
    int *data;
    int last_elem;
    size_t capacity;
} heap;

heap *new_heap();
void insert(heap* h, int val);
bool is_empty(heap* h);
void propagate_up(heap* h, int index);
void propagate_down(heap* h, int index);

#endif