#include "heap.h"

void siftDown(uint16_t arr[], uint16_t start, uint16_t curr, uint16_t end, CompFunc compare)
{
    assert(start <= end);
    assert(start <= curr);
    assert(curr <= end);

    uint16_t leftChild = 2 * (curr - start) + 1 + start;
    uint16_t rightChild = 2 * (curr - start) + 2 + start;
    uint16_t swapIndex = curr;

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

    if (swapIndex == curr)
        return; // the parent is already the max; holds the heap property

    swap(arr, curr, swapIndex);
    siftDown(arr, start, swapIndex, end, compare);
}

void heapify(uint16_t arr[], uint16_t start, uint16_t end, CompFunc compare)
{
    // Execute siftDown on every parent
    for (int16_t i = (int16_t)(start + (end - start - 1) / 2); i >= start; i--)
    {
        siftDown(arr, start, i, end, compare);
    }
}

void heapSort(uint16_t arr[], uint16_t start, uint16_t end, CompFunc compare)
{
    heapify(arr, start, end, compare);

    for (int16_t i = end; i > start; i--)
    {
        swap(arr, start, i);
        siftDown(arr, start, start, i - 1, compare);
    }
}

void minHeapSort(uint16_t arr[], uint16_t size)
{
    #ifdef DEBUG
    heapSort(arr, 0, size - 1, lt);
    #else
    heapSort(arr, 0, size - 1, compareLt);
    #endif
}

uint16_t minHeapSelect(uint16_t arr[], uint16_t start, uint16_t end, uint16_t k)
{
    assert(start < end);
    assert(start < k);
    assert(k <= end + 1);

    #ifdef DEBUG
    heapify(arr, start, end, lt);
    #else
    heapify(arr, start, end, compareLt);
    #endif

    for (int16_t i = end; i >= k; i--)
    {
        swap(arr, start, i);

        #ifdef DEBUG
        siftDown(arr, start, start, i - 1, lt);
        #else
        siftDown(arr, start, start, i - 1, compareLt);
        #endif
    }

    return start;
}

uint16_t maxHeapSelect(uint16_t arr[], uint16_t start, uint16_t end, uint16_t k)
{
    assert(start < end);
    assert(start < k);
    assert(k <= end + 1);

    #ifdef DEBUG
    heapify(arr, start, end, gt);
    #else
    heapify(arr, start, end, compareGt);
    #endif

    for (int16_t i = end; i >= k; i--)
    {
        swap(arr, start, i);

        #ifdef DEBUG
        siftDown(arr, start, start, i - 1, gt);
        #else
        siftDown(arr, start, start, i - 1, compareGt);
        #endif
    }

    return start;
}
