#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../../common/heap.h"
#include "../../common/bst.h"
#include "../../common/util.h"
#include "../../common/COMPARE.h"

#ifdef DEBUG
CompFunc compare = gt;
#else
CompFunc compare = compareGt;
#endif

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
    int *elements = malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++)
        elements[i] = i + 1;

    for (int i = 0; i < k; i++)
        Best[i] = elements[i];

    // Sort the first k values
    resetComps();
    minHeapSort(Best, k);
    printf("Sort comparisons: %d\n", getComps());
    printf("Add to BST comparisons: %d\n", n - k);

    int insertComps = 0;

    for (int i = k; i < n; ++i)
    {
        if (compare(elements[i], Best[k - 1]))
        {
            getComps();
            node *tree = bstConstruct(Best, 0, k - 2);
            bstInsert(tree, elements[i]);

            int * newBest = bstToArray(tree, k);
            for (int j = 0; j < k; j++)
                Best[j] = newBest[j];

            insertComps += getComps();
            free(newBest);
            bstDestroy(tree);
        }
    }

    printf("Insert comparisons: %d\n", insertComps);
    printf("Total comparisons: %d\n\n", allComps());

    free(elements);
    return 1; // No errors
}
