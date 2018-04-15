#include "util.h"

// rand returns a random index for an array of the specified size.
// This is used to get the random pivot for use in QuickSelect.
uint16_t randIndex(uint16_t size)
{
    return dshrandom(0) * (size - 1);
}

// swap modifies the given array by swapping two elements in place.
void swap(uint16_t arr[], uint16_t a, uint16_t b)
{
    uint16_t prevA = arr[a];
    arr[a] = arr[b];
    arr[b] = prevA;
}

// max chooses the largest of the two specified numbers.
uint16_t max(uint16_t a, uint16_t b)
{
    return a > b ? a : b;
}

// min chooses the smallest of the two specified numbers.
uint16_t min(uint16_t a, uint16_t b)
{
    return a < b ? a : b;
}

// debug prints out the array specified
void debug(uint16_t arr[], uint16_t start, uint16_t end)
{
    printf("Array: ");
    for (uint16_t i = start; i <= end; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// shift modifies the given array to move the specified element to the left
// or right a number of times. This shifts the rest of the elements around.
void shift(uint16_t arr[], uint16_t pos, int shiftAmount)
{
    uint16_t element = arr[pos];
    if (shiftAmount > 0)
    {
        // Shift right
        for (uint16_t i = pos; i < pos + shiftAmount; i++)
        {
            arr[i] = arr[i + 1];
        }
    }
    else if (shiftAmount < 0)
    {
        // Shift left
        for (uint16_t i = pos; i > pos + shiftAmount; i--)
        {
            arr[i] = arr[i - 1];
        }
    }
    arr[pos + shiftAmount] = element;
}

// split takes the specified array and splits it into several parts.
uint16_t** split(uint16_t arr[], uint16_t size, uint16_t splits)
{
    assert(size % splits == 0);

    uint16_t** results;
    uint16_t splitSize = size / splits;

    results = malloc(sizeof(uint16_t*) * splits);
    for (uint16_t i = 0; i < splits; i++)
    {
        results[i] = malloc(sizeof(uint16_t) * splitSize);
    }

    return results;
}

static int lastComps = 0;
static int totalComps = 0;

int getComps(void)
{
    int recentComps = COMPARE(-1, -1) - totalComps;
    lastComps = recentComps;
    totalComps += recentComps;
    return recentComps;
}

int allComps(void)
{
    return totalComps;
}

void resetComps(void)
{
    lastComps = 0;
    totalComps = 0;
}
