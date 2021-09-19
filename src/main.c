#include <stdio.h>

#include "heap.h"


int integer_comparator(void* item1, void* item2)
{
    return *(uint32_t*)item1 - *(uint32_t*)item2;
}


int main()
{
    uint32_t data[] = {4, 1, 9, 3, 456, 0, 65, 23, 88, 2};
    heap_inplace_sort(data, sizeof(data) / sizeof(uint32_t), sizeof(uint32_t), integer_comparator, true);
    for (uint32_t i = 0; i < sizeof(data) / sizeof(uint32_t); i++)
    {
        printf("%d ", data[i]);
    }
    printf("\n");
    return 0;
}
