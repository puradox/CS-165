#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#include "../common/bst.h"
#include "../common/util.h"

int doalg(int n, int k, int Best[]);

// Construct a binary search tree and iteratively add to it.
// Returns 1 if there were no errors, 0 otherwise.
//
// Bounds:
//   10 <= n <= 10000
//   1  <= k <= 100
int doalg(int n, int k, int Best[])
{
    // Represent values by their indices
    uint16_t *elements = malloc(sizeof(uint16_t) * (uint16_t)n);
    for (uint16_t i = 0; i < n; i++)
        elements[i] = i + 1;

    // Sort the k maximum values
    //maxHeapSelect(elements, 0, (uint16_t)(n - 1), (uint16_t)(n - k));
    //printf("Comparisons: %d\n", getComps());
    //resetComps();

    // Copy results over
    for (int i = n - 1; i >= n - k; i--)
        Best[n - i - 1] = elements[i];

    free(elements);
    return 1; // No errors
}
