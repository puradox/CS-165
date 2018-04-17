#include <assert.h>
#include <math.h>

#include "tournament.h"

#ifdef DEBUG
CompFunc compare = gt;
#else
CompFunc compare = compareGt;
#endif

player *tournamentConstruct(int arr[], int start, int end)
{
    assert(arr != NULL);
    assert(start <= end);

    int size = end - start;
    player **players = malloc(sizeof(player *) * size);

    // Construct the initial players
    for (int i = 0; i < size; i++)
    {
        player *p = malloc(sizeof(player));
        p->value = arr[start + i + 1];
        p->left = NULL;
        p->right = NULL;
        p->predecessor = NULL;
        players[i] = p;
    }

    // Run the tournament
    while (size > 1)
    {
        int half = (int)(ceil((double)size / 2.0));
        player **winners = malloc(sizeof(player *) * half);

        for (int i = 0; i < half; i++)
        {
            player *winner = malloc(sizeof(player));

            // Find the left competitor
            player *left = players[i * 2];
            winner->left = left;

            if (i * 2 + 1 >= size) // There's no right competitor
            {
                winner->value = left->value;
                winner->right = NULL;
                winner->predecessor = left;

                winners[i] = winner;
                break;
            }

            // Find the right competitor
            player *right = players[i * 2 + 1];
            winner->right = right;

            if (compare(left->value, right->value)) // left > right
            {
                winner->value = left->value;
                winner->predecessor = left;
            }
            else // right >= left
            {
                winner->value = right->value;
                winner->predecessor = right;
            }

            winners[i] = winner;
        }

        // Prepare for the next round
        size = half;
        free(players);
        players = winners;
    }

    player *champion = players[0];
    free(players);
    return champion;
}

void tournamentInsert(player *champion, int value)
{
    assert(champion != NULL);
    assert(value > 0);

    if (champion->predecessor == NULL) // Reached the first contestants
    {
        champion->value = value;
        return;
    }

    tournamentInsert(champion->predecessor, value);

    if (champion->right == NULL) // Solo contestant
    {
        champion->value = champion->predecessor->value;
    }
    else if (compare(champion->left->value, champion->right->value)) // left > right
    {
        champion->value = champion->left->value;
        champion->predecessor = champion->left;
    }
    else // right >= left
    {
        champion->value = champion->right->value;
        champion->predecessor = champion->right;
    }
}

void tournamentDestroy(player *champion)
{
    assert(champion != NULL);

    if (champion->left != NULL)
        tournamentDestroy(champion->left);
    if (champion->right != NULL)
        tournamentDestroy(champion->right);

    free(champion);
}
