#include "util.h"

// rand returns a random index for an array of the specified size.
// This is used to get the random pivot for use in QuickSelect.
int randIndex(int size)
{
    return dshrandom(0) * (size - 1);
}

// swap modifies the given array by swapping two elements in place.
void swap(int arr[], int a, int b)
{
    int prevA = arr[a];
    arr[a] = arr[b];
    arr[b] = prevA;
}

// max chooses the largest of the two specified numbers.
int max(int a, int b)
{
    return a > b ? a : b;
}

// min chooses the smallest of the two specified numbers.
int min(int a, int b)
{
    return a < b ? a : b;
}

// debug prints out the array specified
void debug(int arr[], int start, int end)
{
    printf("Array: ");
    for (int i = start; i <= end; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// shift modifies the given array to move the specified element to the left
// or right a number of times. This shifts the rest of the elements around.
void shift(int arr[], int pos, int shiftAmount)
{
    int element = arr[pos];
    if (shiftAmount > 0)
    {
        // Shift right
        for (int i = pos; i < pos + shiftAmount; i++)
        {
            arr[i] = arr[i + 1];
        }
    }
    else if (shiftAmount < 0)
    {
        // Shift left
        for (int i = pos; i > pos + shiftAmount; i--)
        {
            arr[i] = arr[i - 1];
        }
    }
    arr[pos + shiftAmount] = element;
}

static int totalComps = 0;

int getComps(void)
{
    int recentComps = COMPARE(-1, -1) - totalComps;
    totalComps += recentComps;
    return recentComps;
}

int allComps(void)
{
    return totalComps;
}

void resetComps(void)
{
    totalComps = 0;
}
