#include <stdio.h>
#include <unistd.h>
// #include <argp.h>
#include <sys/time.h>

#include "heap.h"

#define TESTS_COUNT 10


int integer_comparator(const void* item1, const void* item2)
{
    return (*(uint32_t*)item1 >= *(uint32_t*)item2) - (*(uint32_t*)item1 <= *(uint32_t*)item2);
}

void get_random_data(void* storage, uint32_t n_bytes)
{
    FILE* source = fopen("/dev/urandom", "rb");
    fread(storage, 1, n_bytes, source);
    fclose(source);
}

bool check_sorted_sequence(
    void* storage, uint32_t items_count, uint32_t item_size,
    int(*comparator)(const void*, const void*), bool ascending
)
{
    if (items_count == 0)
    {
        return true;
    }
    for (uint32_t i = 0; i < items_count - 1; i++)
    {
        int comparing_result = comparator(
            (void*)((uint8_t*)storage + (item_size * i)),
            (void*)((uint8_t*)storage + (item_size * (i + 1)))
        );
        if (((comparing_result < 0) && !ascending) || ((comparing_result > 0) && ascending))
        {
            return false;
        }
    }
    return true;
}

int64_t get_current_microsecond(void)
{
    struct timeval time;
    gettimeofday(&time, NULL);
    return ((time.tv_usec) + (time.tv_sec * 1000000));
}

int main()
{
    uint32_t data[65536];
    int64_t microseconds_sum = 0;
    for (uint32_t i = 0; i < TESTS_COUNT; i++)
    {
        get_random_data(data, sizeof(data));
        int64_t start_microsecond = get_current_microsecond();
        heap_inplace_sort(data, sizeof(data) / sizeof(uint32_t), sizeof(uint32_t), integer_comparator, true);
        int64_t microseconds_elapsed = get_current_microsecond() - start_microsecond;
        if (!check_sorted_sequence(data, sizeof(data) / sizeof(uint32_t), sizeof(uint32_t), integer_comparator, true))
        {
            printf("ERROR!\n");
            _exit(1);
        }
        microseconds_sum += microseconds_elapsed;
        printf(
            "Test %u: elapsed %ld.%ld milliseconds\n", i + 1,
            microseconds_elapsed / 1000,
            microseconds_elapsed % 1000
        );
    }
    int64_t microseconds_avg = microseconds_sum / TESTS_COUNT;
    printf(
        "AVERAGE: %ld.%ld milliseconds\n",
        microseconds_avg / 1000,
        microseconds_avg % 1000
    );
    return 0;
}
