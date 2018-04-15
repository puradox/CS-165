#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#include "../common/heap.h"
#include "../common/util.h"

uint16_t partition(uint16_t arr[], uint16_t start, uint16_t end, uint16_t pivot);
uint16_t dselect(uint16_t arr[], uint16_t start, uint16_t end, uint16_t k);
int doalg(int n, int k, int Best[]);

// partition partially sorts the array within the given range around a ranomly
// generated pivot. The array will partially sorted in ascending order by the
// pivot value.
uint16_t partition(uint16_t arr[], uint16_t start, uint16_t end, u_int16_t pivot)
{
    assert(start < end);
    assert(start <= pivot);
    assert(pivot <= end);

    // Move the pivot to the end temporarily so we can find it's new position.
    swap(arr, pivot, end);

    // Find a new place for the pivot by partially sorting.
    uint16_t cursor = start;
    for (uint16_t i = start; i < end; i++)
    {
        #ifdef DEBUG
        if (gt(arr[i], arr[end]))
        #else
        if (compareGt(arr[i], arr[end]))
        #endif
        {
            swap(arr, cursor, i);
            cursor++;
        }
    }

    // Put the pivot in its correct place.
    swap(arr, cursor, end);

    // Return the absolute position of the pivot.
    return cursor;
}

const static uint16_t SIZE_CUTOFF = 10;
const static uint16_t SPLIT_SIZE = 8;

// dselect runs a modified version of the deterministic selection algorithm to
// partially sort the array specified in ascending order.
// From index 0 to k, you will find the k largest elements of in the array.
uint16_t dselect(uint16_t arr[], uint16_t start, uint16_t end, uint16_t k)
{
    if (start == end)
        return k - 1;

    assert(start < end);
    assert(start < k);
    assert(k <= end + 1);

    const uint16_t size = end - start + 1;

    if (size < SIZE_CUTOFF)
        return minHeapSelect(arr, start, end, k);

    const uint16_t splitAmount = (uint16_t)(ceil((double)size / (double)SPLIT_SIZE));
    uint16_t *middles = malloc(sizeof(uint16_t) * (uint16_t)splitAmount);

    for (uint16_t split = 0; split < splitAmount; split++)
    {
        const uint16_t splitStart = start + split * SPLIT_SIZE;
        const uint16_t splitEnd = min(splitStart + SPLIT_SIZE - 1, end);
        const uint16_t splitSize = splitEnd - splitStart + 1;
        const uint16_t splitK = (uint16_t)(ceil((double)splitSize / 2.0) + splitStart);
        const uint16_t splitMedian = dselect(arr, splitStart, splitEnd, splitK);
        middles[split] = arr[splitMedian];
    }

    const uint16_t middlesK = (uint16_t)(ceil((double)splitAmount / 2.0));
    const uint16_t middlesMedian = dselect(middles, 0, splitAmount - 1, middlesK);
    int16_t pivotIndex = -1;
    for (int16_t i = (int16_t)start; i <= end; i++)
    {
        if (arr[i] == middles[middlesMedian])
        {
            pivotIndex = i;
            break;
        }
    }
    assert(pivotIndex != -1);
    free(middles);

    const uint16_t pivot = partition(arr, start, end, (uint16_t)pivotIndex);

    // Check the pivot position
    if (k - 1 < pivot)
        return dselect(arr, start, pivot - 1, k);
    else if (k - 1 > pivot)
        return dselect(arr, pivot + 1, end, k);

    return k - 1;
}

// Performs Quick Select and stores the k largest elements in
// the specified "Best" array.
// Returns 1 if there were no errors, 0 otherwise.
//
// Bounds:
//   10 <= n <= 10000
//   1  <= k <= 100
int doalg(int n, int k, int Best[])
{
    // Represent values by their indices
    uint16_t *elements = malloc(sizeof(uint16_t) * (uint16_t)n);
    for (uint16_t i = 0; i < n; i++)
        elements[i] = i + 1;

    dselect(elements, 0, (uint16_t)n - 1, (uint16_t)k);
    int selectComps = getComps();

    // Sort the k maximum values
    minHeapSort(elements, (uint16_t)k);
    int sortComps = getComps();
    printf("Comparisons: select (%d) + sort (%d) = %d\n", selectComps, sortComps, allComps());
    resetComps();

    // Copy results over
    for (uint16_t i = 0; i < k; i++)
        Best[i] = elements[i];

    free(elements);
    return 1; // No errors
}
