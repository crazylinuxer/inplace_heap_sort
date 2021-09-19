#include <stdio.h>
#include <string.h>

#include "heap.h"


int integer_comparator(const void* item1, const void* item2)
{
    return *(uint32_t*)item1 - *(uint32_t*)item2;
}

int str_comparator(const void* item1, const void* item2)
{
    return strcmp(*(const char**)item1, *(const char**)item2);
}

int main()
{
    uint32_t data[] = {4, 1, 9, 3, 456, 0, 65, 23, 88, 2};
    const char* data2[] = {"dfgdf", "kghjgkhj", "asdfads", "jghjgh", "fghfgh", "abc", "----_1"};
    heap_inplace_sort(data, sizeof(data) / sizeof(uint32_t), sizeof(uint32_t), integer_comparator, true);
    for (uint32_t i = 0; i < sizeof(data) / sizeof(uint32_t); i++)
    {
        printf("%d ", data[i]);
    }
    printf("\n");
    heap_inplace_sort(data2, sizeof(data2) / sizeof(char*), sizeof(char*), str_comparator, true);
    for (uint32_t i = 0; i < sizeof(data2) / sizeof(char*); i++)
    {
        printf("%s\n", data2[i]);
    }
    printf("\n");
    return 0;
}
