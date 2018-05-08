#include <stdio.h>
#include "perf.h"

void init_count()
{
    COUNT_TOTAL = 0;
    COUNT_TRIPLET = 0;
    COUNT_TRIPLET_HARD = 0;
    COUNT_PAIR = 0;
    COUNT_SINGLETON = 0;
}

void print_count()
{
    printf("\n%d total\n", COUNT_TOTAL);
    printf(" |-> %d triplets\n", COUNT_TRIPLET);
    printf(" |-> %d hard triplets\n", COUNT_TRIPLET_HARD);
    printf(" |-> %d pairs\n", COUNT_PAIR);
    printf(" |-> %d singletons\n", COUNT_SINGLETON);
    printf(" |-> %d find calls\n", COUNT_FIND);
}

int inc_find()
{
    ++COUNT_TOTAL;
    return ++COUNT_FIND;
}
int inc_triplet_hard()
{
    ++COUNT_TOTAL;
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
