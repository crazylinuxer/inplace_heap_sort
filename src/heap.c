#include <string.h>

#include "include/heap.h"


void heap_init(
    heap* self, void* storage, int(*comparator)(void*, void*),
    bool max_heap, uint32_t item_size, uint32_t storage_size
)
{
    self->storage = storage;
    self->comparator = comparator;
    self->max_heap = max_heap;
    self->item_size = item_size;
    self->storage_size = storage_size;
    self->items_count = 0;
}

static void exchange(void* item1, void* item2, uint32_t item_size)
{
    uint8_t item_tmp_storage[item_size];
    memcpy(item_tmp_storage, item1, item_size);
    memmove(item1, item2, item_size);
    memcpy(item2, item_tmp_storage, item_size);
}

/// -1 if does not exist
static int32_t get_left(heap* self, uint32_t index)
{
    index *= 2;
    index += 1;
    if (index > (self->item_size * self->items_count))
    {
        return -1;
    }
    return (int32_t)index;
}

/// -1 if does not exist
static int32_t get_right(heap* self, uint32_t index)
{
    index *= 2;
    index += 2;
    if (index > (self->item_size * self->items_count))
    {
        return -1;
    }
    return (int32_t)index;
}

/// -1 if does not exist
static int32_t get_parent(uint32_t index)
{
    return (index / 2) - (int32_t)(!(bool)(index % 2));
}

static void flow_up(heap* self)
{
    uint32_t current_item_index = self->items_count - 1;
    while (true)
    {
        uint32_t parent_item_index = get_parent(current_item_index);
        if (parent_item_index == -1)
        {
            return;
        }
        void* parent_item = (void*)((uint8_t*)self->storage + (parent_item_index * self->item_size));
        void* current_item = (void*)((uint8_t*)self->storage + (current_item_index * self->item_size));
        int comparing_result = self->comparator(current_item, parent_item);
        if (((comparing_result > 0) && (self->max_heap)) || ((comparing_result < 0) && (!self->max_heap)))
        // ((current_item > parent_item) && (max_heap)) || ((current_item < parent_item) && (!max_heap))
        {
            exchange(current_item, parent_item, self->item_size);
        }
        else
        {
            return;
        }
    }
}

static void flow_down(heap* self)
{
    int32_t current_item_index = 0;
    while (true)
    {
        int32_t left_index = get_left(self, current_item_index);
        int32_t right_index = get_right(self, current_item_index);
        void* current_item = (void*)((uint8_t*)self + (current_item_index * self->item_size));
        void* left = (void*)((uint8_t*)self + (left_index * self->item_size)); // unsafe ptr; use only if left_index != -1
        void* right = (void*)((uint8_t*)self + (right_index * self->item_size)); // unsafe ptr; use only if right_index != -1
        if ((left_index != -1) && (right_index != -1))
        {
            int lr_comparing_result = self->comparator(left_index, right_index);
            if (((lr_comparing_result == 1) && self->max_heap) || ((lr_comparing_result == -1) && !self->max_heap))
            {
                right_index = -1;
            }
            else
            {
                left_index = -1;
            }
        }
        if (left_index != -1)
        {
            int comparing_result = self->comparator(current_item, left);
            if (((comparing_result > 0) && (!self->max_heap)) || ((comparing_result < 0) && (self->max_heap)))
            {
                exchange(left, current_item, self->item_size);
            }
        }
        else if (right_index != -1)
        {
            int comparing_result = self->comparator(current_item, right);
            if (((comparing_result > 0) && (!self->max_heap)) || ((comparing_result < 0) && (self->max_heap)))
            {
                exchange(right, current_item, self->item_size);
            }
        }
        else
        {
            return;
        }
    }
}

bool heap_insert(heap* self, void* item)
{
    if (self->items_count == self->storage_size)
    {
        return false;
    }
    memcpy(
        (void*)((uint8_t*)self->storage + (self->item_size * self->items_count)),
        item,
        self->item_size
    );
    self->items_count++;
    flow_up(self);
    return true;
}

bool heap_pop(heap* self, void* item_receiver)
{
    if (self->items_count == 0)
    {
        return false;
    }
    memcpy(item_receiver, self->storage, self->item_size);
    self->items_count--;
    if (self->items_count)
    {
        memmove(
            self->storage,
            (void*)(
                (uint8_t*)self->storage + (self->item_size * self->items_count)
            ),
            self->item_size
        );
        flow_down(self);
    }
    return true;
}

void heap_inplace_heapify(
    heap* dest, void* array, uint32_t size,
    int(*comparator)(void*, void*), bool max_heap, uint32_t item_size
);

void heap_inplace_sort(void* array, uint32_t size);
