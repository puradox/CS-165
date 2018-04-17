#ifndef TOURNAMENT_H
#define TOURNAMENT_H

#include "COMPARE.h"
#include "util.h"

struct player
{
    int value;
    struct player *left;
    struct player *right;
    struct player *predecessor;
};

typedef struct player player;

// tournamentConstruct constructs a binary tree modeled to work with the
// tournament algorithm. Returns the champion of the tournament.
player *tournamentConstruct(int arr[], int start, int end);

// tournamentInsert replaces the champion with a new player and re-runs
// the tournament.
void tournamentInsert(player *champion, int value);

// tournamentDestroy frees all resources used by the tournament.
void tournamentDestroy(player *champion);

#endif
