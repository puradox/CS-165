#include <stdio.h>

typedef unsigned short uint; // 0 to 65,535

// Rand returns a random number between 1 and the specified max.
// This is used to get the random pivot for use in QuickSelect.
int rand(int max)
{
    return dshrandom(0) * max + 1;
}

// Performs Quick Select and stores the k largest elements in
// the specified "Best" array.
// Returns 1 if there were no errors, 0 otherwise.
//
// Bounds:
//   10 <= n <= 10000
//   1  <= k <= 100
int doalg(int n, int k, int Best[])
{
    printf("n=%d, k=%d\n", n, k);

    // Since we don't have access to the actual values, we need to have
    // some sort of representation for them. I will choose to represent
    // them by their indices.
    uint* elements = malloc(sizeof(uint)*k);
    for (uint i = 0; i < n; i++) {
        elements[i] = i + 1;
    }

    return 1; // Return with no errors for the time being.
}
