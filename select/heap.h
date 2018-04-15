#ifndef HEAP_H
#define HEAP_H

#include <stdint.h>
#include "COMPARE.h"
#include "util.h"

typedef int8_t (*CompFunc)(uint16_t, u_int16_t);

// Comparators
int8_t lt(uint16_t a, uint16_t b);
int8_t gt(uint16_t a, uint16_t b);
int8_t compareLt(uint16_t a, uint16_t b); // uses COMPARE
int8_t compareGt(uint16_t a, uint16_t b); // uses COMPARE

// siftDown enforces the max-heap property by starting at the specified node and
// propogating down the tree, swapping elements until that branch looks correct.
void siftDown(uint16_t arr[], uint16_t start, uint16_t curr, uint16_t end, CompFunc compare);

// heapify creates a max heap in-place with the given array.
// Brotip: If end is equal to the size of the array, the entire array is
// converted a heap.
void heapify(uint16_t arr[], uint16_t start, uint16_t end, CompFunc compare);

// heapSort sorts the array in in-place using the specified compare function.
void heapSort(uint16_t arr[], uint16_t start, uint16_t end, CompFunc compare);
void minHeapSort(uint16_t arr[], uint16_t size);

// heapSelect selects the kth element in the sorted array.
// Runs in O(k log n) time.
uint16_t minHeapSelect(uint16_t arr[], uint16_t start, uint16_t end, uint16_t k);

#endif
