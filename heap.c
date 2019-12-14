#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "heap.h"
#include <math.h>

#define SWAP(type,a,b)          { type tmp = a; a = b; b = tmp; }

heap *new_heap() {
    heap* h = malloc(sizeof(heap));
    int* d = malloc(sizeof(int) * HEAP_SIZE);

    h->data = d;
    h->capacity = (size_t)HEAP_SIZE;
    // index=0 is always empty
    h->last_elem = ROOT_INDEX;

    return h;
};

void insert(heap* h, int val) {
    h->data[h->last_elem] = val;
    propagate_up(h, h->last_elem);
    h->last_elem++;
}

int pop(heap* h) {
    if (is_empty(h)) {
        return -1;
    }
    int ret = h->data[ROOT_INDEX];
    int new_root = h->data[h->last_elem - 1];

    h->data[ROOT_INDEX] = new_root;
    h->last_elem--;
    propagate_down(h, ROOT_INDEX);
    return ret;
}

void propagate_up(heap* h, int index) {
    if (index <= ROOT_INDEX) {
        return;
    }
    int parent = index / 2;
    if (h->data[index] < h->data[parent]) {
        SWAP(int, h->data[index], h->data[parent]);
        propagate_up(h, parent);
    }
}

void propagate_down(heap* h, int index) {
    if (index >= h->last_elem) {
        return;
    }
    int left = index * 2;
    int right = left + 1;
    int smallest = index;
    if (left < h->last_elem && h->data[left] < h->data[smallest]) {
        smallest = left;
    }
    if (right < h->last_elem && h->data[right] < h->data[smallest]) {
        smallest = right;
    }
    if (smallest != index) {
        SWAP(int, h->data[index], h->data[smallest]);
        propagate_down(h, smallest);
    }
}

bool is_empty(heap* h) {
    return h->last_elem <= ROOT_INDEX;
}

void print_heap(heap* h) {
    int depth = (int)ceil(log2(h->last_elem));
    for (int i = 1; i < h->last_elem; i++) {
        printf("%d\n", h->data[i]);
    }
    printf("depth ---> %d \n", depth);
    printf("last_elem ---> %d \n", h->last_elem);
}

int main() {
    heap* h = new_heap();
    insert(h, 3);
    insert(h, 4);
    insert(h, 8);
    insert(h, 2);
    insert(h, 1);
    insert(h, 10);
    insert(h, 9);
    insert(h, 22);
    // printf("heap capacity ---> %d", h->capacity)
    // printf("heap last     ---> %d", h->last_elem);
    print_heap(h);
    while (!is_empty(h)) {
        int smallest = pop(h);
        printf("smallest %d\n", smallest);
    }
    return 0;
};
