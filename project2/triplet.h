#ifndef TRIPLET_H
#define TRIPLET_H

#define false 0
#define true 1

// Triplet holds information of the QCOUNT evaluation of some reference
// points and a number of unique elements from the original array.
typedef struct
{
    int count;
    int startingIndex;

    // Triplets are of size 3, pairs of size 2, singletons of size 1.
    int size;

    // The first triplet is not accounted for when it's count is 2.
    // The only way it gets counted is to check against other triplets.
    char accountedFor; // Has this triplet been added to the count?
} triplet;

// Triplet store is a circular queue for holding triplets.
typedef struct
{
    int cursor;
    int tail;
    int head;
    int size;
    int capacity;
    triplet *triplets;
} triplet_store;

// Triplet creation functions
triplet make_first_hard();
triplet make_triplet(int count, int start);
triplet make_pair(int count, int start);
triplet make_singleton(int count, int start);
triplet make_error();

// Utility functions for triplets
char is_error(triplet t); // Checks if a triplet resulted in an error
void assert_triplet(triplet t); // Assert that a triplet is valid

// Global stores for useful triplets
triplet_store *store_AAB; // AAB or ABA or BAA
triplet_store *store_ABB; // ABB or BAB or BBA

// Store methods
triplet_store *make_store(int size); // Make a new store
void free_store(triplet_store *s); // Free the memory of a store
int store_sizeof(triplet_store *s); // Counts triplets in a store
triplet store_push(triplet_store *s, triplet t); // Push a triplet to a store
triplet store_pop(triplet_store *s); // Pop a triplet from a store

#endif
