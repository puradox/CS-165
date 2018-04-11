#include "heap.h"

int8_t compareLt(uint16_t a, uint16_t b)
{
    return (uint8_t)COMPARE(a, b) == 2;
}

int8_t compareGt(uint16_t a, uint16_t b)
{
    return (uint8_t)COMPARE(a, b) == 1;
}

int8_t lt(uint16_t a, uint16_t b)
{
    return a < b;
}

int8_t gt(uint16_t a, uint16_t b)
{
    return a > b;
}

void siftDown(uint16_t arr[], uint16_t start, uint16_t end, CompFunc compare)
{
    uint16_t leftChild = 2 * start + 1;
    uint16_t rightChild = 2 * start + 2;
    uint16_t swapIndex = start;

    if (leftChild > end)
        return;

    // Compare left and right children to the parent to find the maximum.
    if (compare(arr[leftChild], arr[swapIndex])) // left < swap
    {
        swapIndex = leftChild;
    }
    if (rightChild <= end && compare(arr[rightChild], arr[swapIndex])) // right < swap
    {
        swapIndex = rightChild;
    }

    if (swapIndex == start)
        return; // the parent is already the max; holds the heap property

    swap(arr, start, swapIndex);
    siftDown(arr, swapIndex, end, compare);
}

void heapify(uint16_t arr[], uint16_t start, uint16_t end, CompFunc compare)
{
    // Execute siftDown on every parent
    for (int16_t i = start + (end - 1) / 2; i >= start; i--)
    {
        siftDown(arr, i, end, compare);
    }
}

void heapSort(uint16_t arr[], uint16_t start, uint16_t end, CompFunc compare)
{
    heapify(arr, start, end, compare);

    for (int16_t i = end; i > start; i--)
    {
        swap(arr, start, i);
        siftDown(arr, start, i - 1, compare);
    }
}

void maxHeapSort(uint16_t arr[], uint16_t size)
{
    heapSort(arr, 0, size - 1, compareLt);
}

void minHeapSort(uint16_t arr[], uint16_t size)
{
    heapSort(arr, 0, size - 1, compareGt);
}

int16_t heapSelect(uint16_t arr[], uint16_t start, uint16_t end, uint16_t k)
{
    if (k < 0 || k > end - start)
        return -1;

    heapify(arr, start, end, compareGt);

    for (int16_t i = end; i >= start + k - 1; i--)
    {
        swap(arr, start, i);
        siftDown(arr, start, i - 1, compareGt);
    }

    return arr[start + k - 1];
}
