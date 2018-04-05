#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

// Let's define an integer with a width of 16 bits.
// Indices never go above 10,000 and we don't deal with actual values.
typedef signed short int16;    // –32,768 to 32,767
typedef unsigned short uint16; // 0 to 65,535

// Helper functions
int randIndex(uint16);                // returns a random index for an array of given size
void swap(uint16[], uint16, uint16);  // swaps two elements in an array
uint16 max(uint16, uint16);           // returns the max argument
void debug(uint16[], uint16, uint16); // prints out the array from start to end

// partition partially sorts the array within the given range around a ranomly
// generated pivot. The array will partially sorted in ascending order by the
// pivot value.
uint16 partition(uint16 arr[], uint16 start, uint16 end)
{
    // Select the pivot and move it to the end.
    uint16 size = end - start + 1;
    uint16 pivot = randIndex(size) + start;
    swap(arr, pivot, end);

    // Find a new place for the pivot by partially sorting.
    uint16 cursor = start;
    for (uint16 i = start; i < end; i++)
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
void quickselect(uint16 arr[], uint16 start, uint16 end, uint16 k)
{
    if (start == end)
        return;

    uint16 pivot = partition(arr, start, end);

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

// siftDown enforces the max-heap property by starting at the specified node and
// propogating down the tree, swapping elements until that branch looks correct.
void siftDown(uint16 arr[], uint16 start, uint16 end)
{
    uint16 leftChild = 2 * start + 1;
    uint16 rightChild = 2 * start + 2;
    uint16 swapIndex = start;

    if (leftChild > end)
        return;

    // Compare left and right children to the parent to find the maximum.
    if (COMPARE(arr[leftChild], arr[swapIndex]) == 2) // left < swap
    {
        swapIndex = leftChild;
    }
    if (rightChild <= end && COMPARE(arr[rightChild], arr[swapIndex]) == 2) // right < swap
    {
        swapIndex = rightChild;
    }

    if (swapIndex == start)
        return; // the parent is already the max; holds the heap property

    swap(arr, start, swapIndex);
    siftDown(arr, swapIndex, end);
}

// heapify creates a max heap in-place with the given array.
// Brotip: If end is equal to the size of the array, the entire array is
// converted a heap.
void heapify(uint16 arr[], uint16 end)
{
    // Execute siftDown on every parent
    for (int16 start = (end - 1) / 2; start >= 0; start--)
    {
        siftDown(arr, start, end);
    }
}

// heapsort sorts the array in descending order in-place.
void heapSort(uint16 arr[], uint16 size)
{
    heapify(arr, size - 1);

    for (int16 end = size - 1; end > 0; end--)
    {
        swap(arr, 0, end);
        siftDown(arr, 0, end - 1);
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
    uint16 *elements = malloc(sizeof(uint16) * n);
    for (uint16 i = 0; i < n; i++)
    {
        elements[i] = i + 1;
    }

    // Partially sort the array so that the 0 through k indices are the
    // k highest.
    quickselect(elements, 0, n - 1, k);
    int selectComps = -COMPARE(-1, k, Best);

    // Sort arr[0:k] in descending order.
    heapSort(elements, k);
    int sortComps = -(selectComps + COMPARE(-1, k, Best));
    int comps = selectComps + sortComps;
    printf("Comparisons: select (%d) + sort (%d) = %d\n", selectComps, sortComps, comps);

    // Copy the k largest elements to the array of results.
    for (uint16 i = 0; i < k; i++)
    {
        Best[i] = elements[i];
    }

    free(elements);
    return 1; // Return with errors for the time being.
}

//
// Implementation of helper functions
//

// rand returns a random index for an array of the specified size.
// This is used to get the random pivot for use in QuickSelect.
int randIndex(uint16 size)
{
    return dshrandom(0) * (size - 1);
}

// swap modifies the given array by swapping two elements in place.
void swap(uint16 arr[], uint16 a, uint16 b)
{
    uint16 prevA = arr[a];
    arr[a] = arr[b];
    arr[b] = prevA;
}

// max chooses the largest of the two specified numbers.
uint16 max(uint16 a, uint16 b)
{
    return a > b ? a : b;
}

// debug prints out the array specified
void debug(uint16 arr[], uint16 start, uint16 end)
{
    printf("Array: ");
    for (uint16 i = start; i <= end; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

//
// Not used
//

// shift modifies the given array to move the specified element to the left
// or right a number of times. This shifts the rest of the elements around.
void shift(uint16 arr[], uint16 pos, int shiftAmount)
{
    uint16 element = arr[pos];
    if (shiftAmount > 0)
    {
        // Shift right
        for (uint16 i = pos; i < pos + shiftAmount; i++)
        {
            arr[i] = arr[i + 1];
        }
    }
    else if (shiftAmount < 0)
    {
        // Shift left
        for (uint16 i = pos; i > pos + shiftAmount; i--)
        {
            arr[i] = arr[i - 1];
        }
    }
    arr[pos + shiftAmount] = element;
}
