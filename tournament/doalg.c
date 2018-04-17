#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../common/tournament.h"
#include "../common/heap.h"
#include "../common/COMPARE.h"
#include "../common/sorting.h"

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

    // Insert n - k + 1 elements into the tournament.
    player *champion = tournamentConstruct(elements, k - 2, n - 1);

    for (int i = 0; i < k - 1; i++)
    {
        Best[i] = champion->value;
        tournamentInsert(champion, elements[i]);
    }

    Best[k - 1] = champion->value; // The cherry on top

    // Sort Best[] since it's not guaranteed to be sorted already
    insertionSort(Best, k);

    tournamentDestroy(champion);
    free(elements);
    return 1; // No errors
}
