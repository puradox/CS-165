#ifndef HEAP_H
#define HEAP_H

#include "COMPARE.h"
#include "util.h"

// siftDown enforces the max-heap property by starting at the specified node and
// propogating down the tree, swapping elements until that branch looks correct.
void siftDown(int arr[], int start, int curr, int end, CompFunc compare);

// heapify creates a max heap in-place with the given array.
// Brotip: If end is equal to the size of the array, the entire array is
// converted a heap.
void heapify(int arr[], int start, int end, CompFunc compare);

// heapSort sorts the array in in-place using the specified compare function.
void heapSort(int arr[], int start, int end, CompFunc compare);
void minHeapSort(int arr[], int size);
void maxHeapSort(int arr[], int size);

// heapSelect selects the kth element in the sorted array.
// Runs in O(k log n) time.
int minHeapSelect(int arr[], int start, int end, int k);
int maxHeapSelect(int arr[], int start, int end, int k);

#endif
