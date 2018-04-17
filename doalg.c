#include <stdlib.h>
#include <math.h>

//
// compare.h
//

typedef int (*CompFunc)(int, int);

int lt(int a, int b);
int gt(int a, int b);
int compareLt(int a, int b); // uses COMPARE
int compareGt(int a, int b); // uses COMPARE

#ifdef DEBUG
CompFunc compare = gt;
#else
CompFunc compare = compareGt;
#endif

//
// compare.c
//

int compareLt(int a, int b)
{
    return COMPARE(a, b) == 2;
}

int compareGt(int a, int b)
{
    return COMPARE(a, b) == 1;
}

int lt(int a, int b)
{
    return a < b;
}

int gt(int a, int b)
{
    return a > b;
}

//
// tournament.h
//

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

//
// tournament.c
//

player *tournamentConstruct(int arr[], int start, int end)
{
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
    if (champion->left != NULL)
        tournamentDestroy(champion->left);
    if (champion->right != NULL)
        tournamentDestroy(champion->right);

    free(champion);
}

//
// sorting.h
//

// Uses the insertion sort algorithm to sort the passed array in-place.
void insertionSort(int arr[], int len);

//
// sorting.c
//

void insertionSort(int arr[], int len)
{
  for (int i = 1; i < len; i++)
  {
    for (int j = i; j != 0 && compare(arr[j], arr[j - 1]); j--)
    {
      int temp = arr[j];
      arr[j] = arr[j - 1];
      arr[j - 1] = temp;
    }
  }
}

//
// doalg.c
//

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
