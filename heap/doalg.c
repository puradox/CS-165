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
    int *elements = malloc(sizeof(int) * (int)n);
    for (int i = 0; i < n; i++)
        elements[i] = i + 1;

    // Sort the k maximum values
    maxHeapSelect(elements, 0, (int)(n - 1), (int)(n - k));
    //printf("Comparisons: %d\n", getComps());
    //resetComps();

    // Copy results over
    for (int i = n - 1; i >= n - k; i--)
        Best[n - i - 1] = elements[i];

    free(elements);
    return 1; // No errors
}
