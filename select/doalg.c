#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "heap.h"
#include "util.h"

// partition partially sorts the array within the given range around a ranomly
// generated pivot. The array will partially sorted in ascending order by the
// pivot value.
uint16_t partition(uint16_t arr[], uint16_t start, uint16_t end, u_int16_t pivot)
{
    // Move the pivot to the end temporarily so we can find it's new position.
    swap(arr, pivot, end);

    // Find a new place for the pivot by partially sorting.
    uint16_t cursor = start;
    for (uint16_t i = start; i < end; i++)
    {
        if (COMPARE(arr[i], arr[end]) == 1) // arr[i] > pivot
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

// quickselect runs a modified version of the QuickSelect algorithm to
// partially sort the array specified in ascending order.
// From index 0 to k, you will find the k largest elements of in the array.
void quickselect(uint16_t arr[], uint16_t start, uint16_t end, uint16_t k)
{
    if (start == end)
        return;

    uint16_t size = end - start + 1;

/*
    if (size < 10)
    {
        //heapSelect(arr, start, end, k);
        heapSort(arr, start, end, compareGt);
        return;
    }

    uint16_t splitAmount = 5;
    uint16_t splitK = splitAmount / 2 + 1;
    uint16_t splitSize = size / splitAmount;

    for (uint16_t split = 0; split < splitAmount; split++)
    {
        uint16_t startSplit = start + split * splitSize;
        uint16_t endSplit = min(startSplit + splitSize, end);
        quickselect(arr, startSplit, endSplit, splitAmount / 2 + 1);
    }
    */

    uint16_t pivotIndex = randIndex(size) + start;
    uint16_t pivot = partition(arr, start, end, pivotIndex);

    // Check the pivot position
    if (k < pivot)
    {
        quickselect(arr, start, pivot - 1, k);
    }
    else if (k > pivot)
    {
        quickselect(arr, pivot + 1, end, k);
    }
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
    // Since we don't have access to the actual values, we need to have
    // some sort of representation for them. I will choose to represent
    // them by their indices.
    uint16_t *elements = malloc(sizeof(uint16_t) * n);
    for (uint16_t i = 0; i < n; i++)
    {
        elements[i] = i + 1;
    }

    // Partially sort the array so that the 0 through k indices are the
    // k highest.
    quickselect(elements, 0, n - 1, k);
    int selectComps = -COMPARE(-1, k, Best);

    // Sort arr[0:k) in descending order.
    maxHeapSort(elements, k);
    int sortComps = -(selectComps + COMPARE(-1, k, Best));
    int comps = selectComps + sortComps;
    printf("Comparisons: select (%d) + sort (%d) = %d\n", selectComps, sortComps, comps);

    // Copy the k largest elements to the array of results.
    for (uint16_t i = 0; i < k; i++)
    {
        Best[i] = elements[i];
    }

    free(elements);
    return 1; // Return with errors for the time being.
}
