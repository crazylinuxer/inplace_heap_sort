#include <string.h>

#include "include/heap.h"


/// -1 if does not exist
static int64_t get_left(uint64_t index);

/// -1 if does not exist
static int64_t get_right(uint64_t index);

/// -1 if does not exist
static int64_t get_parent(uint64_t index);

static void flow_up(void* heap, heap_cfg config, uint64_t storage_size);

static void flow_down(void* heap, heap_cfg config, uint64_t storage_size);

void heap_insert(void* heap, heap_cfg config, uint64_t storage_size, void* item);

void heap_pop(void* heap, heap_cfg config, uint64_t storage_size, void* item_receiver);

void heap_inplace_heapify(void* array, heap_cfg config, uint64_t storage_size);

void heap_inplace_sort(void* heap, heap_cfg config, uint64_t storage_size);
