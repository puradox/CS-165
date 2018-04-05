#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

// Let's define an integer with a width of 16 bits.
// Indices never go above 10,000 and we don't deal with actual values.
typedef signed short int16;    // –32,768 to 32,767
typedef unsigned short uint16; // 0 to 65,535

// Helper functions
int randIndex(uint16); // returns a random index for an array of given size
void swap(uint16*, uint16, uint16); // swaps two elements in an array
uint16 max(uint16, uint16); // returns the max argument
void debug(uint16*, uint16); // prints out the array

// partition partially sorts the array within the given range around a ranomly
// generated pivot. The array will partially sorted in ascending order by the
// pivot value.
uint16 partition(uint16* arr, uint16 start, uint16 end)
{
    // Select the pivot and move it to the end.
    uint16 size = end - start + 1;
    uint16 pivot = randIndex(size) + start;
    swap(arr, pivot, end);
    pivot = size-1;

    // Find a new place for the pivot by partially sorting.
    uint16 cursor = 0;
    for (uint16 i = start; i < end; i++)
    {
        if (COMPARE(arr[i], arr[pivot]) == 2) // arr[i] > arr[pivot]
        {
            swap(arr, cursor, i);
            cursor++;
        }
    }

    // Put the pivot in its correct place.
    swap(arr, cursor, pivot);

    // Return the absolute position of the pivot.
    return cursor + start;
}

// quickselect runs a modified version of the QuickSelect algorithm to
// partially sort the array specified in ascending order.
// From index 0 to k, you will find the k largest elements of in the array.
void quickselect(uint16 *arr, uint16 start, uint16 end, uint16 k)
{
    if (start == end)
        return;

    uint16 pivot = partition(arr, start, end);

    // Check the pivot position
    printf("Start: %d\nPivot: %d\nEnd: %d\n", start, pivot, end);
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
    printf("n=%d, k=%d\n", n, k);

    // Since we don't have access to the actual values, we need to have
    // some sort of representation for them. I will choose to represent
    // them by their indices.
    uint16 *elements = malloc(sizeof(uint16) * n);
    for (uint16 i = 0; i < n; i++)
    {
        elements[i] = i + 1;
    }

    debug(elements, n);
    quickselect(elements, 0, n-1, k);
    debug(elements, k);

    free(elements);
    return 0; // Return with no errors for the time being.
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
void swap(uint16 *arr, uint16 a, uint16 b)
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
void debug(uint16 *arr, uint16 size)
{
    printf("Array: ");
    for (uint16 i = 0; i < size; i++)
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
void shift(uint16 *arr, uint16 pos, int shiftAmount)
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
