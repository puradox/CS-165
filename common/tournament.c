#include "tournament.h"
#include <assert.h>

player *tournamentConstruct(int arr[], int start, int end)
{
    assert(arr != NULL);
    assert(start <= end);

    return NULL;
}

int tournamentInsert(player *tree, int value)
{
    assert(tree != NULL);
    assert(value > 0);

#ifdef DEBUG
    CompFunc compare = lt;
#else
    CompFunc compare = compareLt;
#endif

    return 0;
}

void tournamentDestroy(player *tree)
{
    assert(tree != NULL);
}
