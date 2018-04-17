#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../common/tournament.h"
#include "../common/util.h"
#include "../common/COMPARE.h"

int doalg(int n, int k, int Best[]);

// Construct a tournament and iteratively add to it.
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

    free(elements);
    return 1; // No errors
}
