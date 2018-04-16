#include "heap.h"

void siftDown(int arr[], int start, int curr, int end, CompFunc compare)
{
    assert(start <= end);
    assert(start <= curr);
    assert(curr <= end);

    int leftChild = 2 * (curr - start) + 1 + start;
    int rightChild = 2 * (curr - start) + 2 + start;
    int swapIndex = curr;

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

void heapify(int arr[], int start, int end, CompFunc compare)
{
    // Execute siftDown on every parent
    for (int i = start + (end - start - 1) / 2; i >= start; i--)
    {
        siftDown(arr, start, i, end, compare);
    }
}

void heapSort(int arr[], int start, int end, CompFunc compare)
{
    heapify(arr, start, end, compare);

    for (int i = end; i > start; i--)
    {
        swap(arr, start, i);
        siftDown(arr, start, start, i - 1, compare);
    }
}

void minHeapSort(int arr[], int size)
{
    #ifdef DEBUG
    heapSort(arr, 0, size - 1, lt);
    #else
    heapSort(arr, 0, size - 1, compareLt);
    #endif
}

void maxHeapSort(int arr[], int size)
{
    #ifdef DEBUG
    heapSort(arr, 0, size - 1, gt);
    #else
    heapSort(arr, 0, size - 1, compareGt);
    #endif
}

int minHeapSelect(int arr[], int start, int end, int k)
{
    assert(start < end);
    assert(start < k);
    assert(k <= end + 1);

    #ifdef DEBUG
    heapify(arr, start, end, lt);
    #else
    heapify(arr, start, end, compareLt);
    #endif

    for (int i = end; i >= k; i--)
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

int maxHeapSelect(int arr[], int start, int end, int k)
{
    assert(start < end);
    assert(start < k);
    assert(k <= end + 1);

    #ifdef DEBUG
    heapify(arr, start, end, gt);
    #else
    heapify(arr, start, end, compareGt);
    #endif

    for (int i = end; i >= k; i--)
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
