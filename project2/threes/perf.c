#include <stdio.h>
#include "perf.h"

void init_count()
{
    COUNT_MYSUB = 0;
    COUNT_EARLY_STOP = 0;
    COUNT_TOTAL = 0;
    COUNT_TRIPLET = 0;
    COUNT_TRIPLET_HARD = 0;
    COUNT_PAIR = 0;
    COUNT_SINGLETON = 0;
}

void print_count()
{
    printf("\n%d total\n", COUNT_TOTAL);
    printf(" |-> %d triplets (%d hard)\n", COUNT_TRIPLET, COUNT_TRIPLET_HARD);
    printf(" |-> %d pairs\n", COUNT_PAIR);
    printf(" |-> %d singletons\n\n", COUNT_SINGLETON);

    printf("%d mysub calls\n", COUNT_MYSUB);
    printf("%d early stops\n", COUNT_EARLY_STOP);
    printf("%d find calls\n", COUNT_FIND);
}

int inc_mysub()
{
    return ++COUNT_MYSUB;
}
int inc_early_stop()
{
    return ++COUNT_EARLY_STOP;
}
int inc_find()
{
    return ++COUNT_FIND;
}
int inc_triplet_hard()
{
    return ++COUNT_TRIPLET_HARD;
}
int inc_triplet()
{
    ++COUNT_TOTAL;
    return ++COUNT_TRIPLET;
}
int inc_pair()
{
    ++COUNT_TOTAL;
    return ++COUNT_PAIR;
}
int inc_singleton()
{
    ++COUNT_TOTAL;
    return ++COUNT_SINGLETON;
}
