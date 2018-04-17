#ifndef TOURNAMENT_H
#define TOURNAMENT_H

#include "COMPARE.h"
#include "util.h"

struct player
{
    int value;
    struct player *leftPredecessor;
    struct player *rightPredecessor;
    struct player *successor;
};

typedef struct player player;

// tournamentConstruct constructs a binary tree modeled to work with the
// tournament algorithm.
player *tournamentConstruct(int arr[], int start, int end);

// tournamentInsert inserts an element into the tournament and returns the
// element that was eliminated.
int tournamentInsert(player *tree, int value);

// tournamentDestroy frees all resources used by the tournament.
void tournamentDestroy(player *tree);

#endif
