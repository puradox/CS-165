#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../../common/heap.h"
#include "../../common/util.h"

int partition(int arr[], int start, int end, int pivot);
int dselect(int arr[], int start, int end, int k);
int doalg(int n, int k, int Best[]);

// partition partially sorts the array within the given range around a ranomly
// generated pivot. The array will partially sorted in ascending order by the
// pivot value.
int partition(int arr[], int start, int end, int pivot)
{
    assert(start < end);
    assert(start <= pivot);
    assert(pivot <= end);

    // Move the pivot to the end temporarily so we can find it's new position.
    swap(arr, pivot, end);

    // Find a new place for the pivot by partially sorting.
    int cursor = start;
    for (int i = start; i < end; i++)
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

const static int SIZE_CUTOFF = 10;
const static int SPLIT_SIZE = 8;

// dselect runs a modified version of the deterministic selection algorithm to
// partially sort the array specified in ascending order.
// From index 0 to k, you will find the k largest elements of in the array.
int dselect(int arr[], int start, int end, int k)
{
    if (start == end)
        return k - 1;

    assert(start < end);
    assert(start < k);
    assert(k <= end + 1);

    const int size = end - start + 1;

    if (size < SIZE_CUTOFF)
        return minHeapSelect(arr, start, end, k);

    const int splitAmount = (int)(ceil((double)size / (double)SPLIT_SIZE));
    int *middles = malloc(sizeof(int) * splitAmount);

    for (int split = 0; split < splitAmount; split++)
    {
        const int splitStart = start + split * SPLIT_SIZE;
        const int splitEnd = min(splitStart + SPLIT_SIZE - 1, end);
        const int splitSize = splitEnd - splitStart + 1;
        const int splitK = (int)(ceil((double)splitSize / 2.0) + splitStart);
        const int splitMedian = dselect(arr, splitStart, splitEnd, splitK);
        middles[split] = arr[splitMedian];
    }

    const int middlesK = (int)(ceil((double)splitAmount / 2.0));
    const int middlesMedian = dselect(middles, 0, splitAmount - 1, middlesK);
    int pivotIndex = -1;
    for (int i = start; i <= end; i++)
    {
        if (arr[i] == middles[middlesMedian])
        {
            pivotIndex = i;
            break;
        }
    }
    assert(pivotIndex != -1);
    free(middles);

    const int pivot = partition(arr, start, end, pivotIndex);

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
    int *elements = malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++)
        elements[i] = i + 1;

    dselect(elements, 0, n - 1, k);
    int selectComps = getComps();

    // Sort the k maximum values
    minHeapSort(elements, k);
    int sortComps = getComps();
    printf("Comparisons: select (%d) + sort (%d) = %d\n", selectComps, sortComps, allComps());
    resetComps();

    // Copy results over
    for (int i = 0; i < k; i++)
        Best[i] = elements[i];

    free(elements);
    return 1; // No errors
}
