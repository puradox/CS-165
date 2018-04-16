#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../common/heap.h"
#include "../common/util.h"

int doalg(int n, int k, int Best[]);

// Performs a partial heap sort to find the k largest elements.
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

    // Create a minheap to (eventually) hold the k largest elements
    int *heap = malloc(sizeof(int) * k);
    for (int i = 0; i < k; i++)
        heap[i] = elements[i];

    #ifdef DEBUG
    heapify(heap, 0, k - 1, lt);
    #else
    heapify(heap, 0, k - 1, compareLt);
    #endif

    int heapifyComps = getComps();
    printf("Heapify comparisions: %d\n", heapifyComps);

    int siftComps = 0;
    int sifts = 0;

    for (int i = k; i < n; i++)
    {
        #ifdef DEBUG
        if (gt(elements[i], heap[0]))
        #else
        if (compareGt(elements[i], heap[0]))
        #endif
        {
            heap[0] = elements[i];

            getComps();
            #ifdef DEBUG
            siftDown(heap, 0, 0, k - 1, lt);
            #else
            siftDown(heap, 0, 0, k - 1, compareLt);
            #endif
            siftComps += getComps();
            sifts++;
        }
    }

    printf("Sift comparisions: %d from %d total sifts\n", siftComps, sifts);
    printf("Adding to heap comparisons: %d\n", n - k);

    // Copy results over
    for (int i = k - 1; i > 0; i--)
    {
        swap(heap, 0, i);

        #ifdef DEBUG
        siftDown(heap, 0, 0, i - 1, lt);
        #else
        siftDown(heap, 0, 0, i - 1, compareLt);
        #endif

        Best[i] = heap[i];
    }

    int sortComps = getComps();
    printf("Sort comps: %d\n", sortComps);
    printf("Total comps: %d\n\n", allComps());

    Best[0] = heap[0];
    free(elements);
    free(heap);
    resetComps();
    return 1; // No errors
}
