#ifndef HEAP_H
#define HEAP_H

#include <stdint.h>
#include <stdbool.h>


typedef struct
{
    uint32_t item_size;
    int (*comparator)(void* item1, void* item2);
    bool max_heap;
}
heap_cfg;


void heap_insert(void* heap, heap_cfg config, uint64_t storage_size, void* item);

void heap_pop(void* heap, heap_cfg config, uint64_t storage_size, void* item_receiver);

void heap_inplace_heapify(void* array, heap_cfg config, uint64_t storage_size);

void heap_inplace_sort(void* heap, heap_cfg config, uint64_t storage_size);

#endif
