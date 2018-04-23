#include <assert.h>
#include <stdlib.h>
#include "triplet.h"

triplet make_first_hard()
{
    return (triplet){0, 2, 3, false}; // not accounted for
}

triplet make_triplet(int count, int start)
{
    assert(count >= -6 && count <= 6);

    triplet result = {count, start, 3, true};
    if (count == -1)
        store_push(store_ABB, result);
    else if (count == 1)
        store_push(store_AAB, result);
    return result;
}

triplet make_pair(int count, int start)
{
    return (triplet){count, start, 2, true};
}

triplet make_singleton(int count, int start)
{
    return (triplet){count, start, 1, true};
}

triplet make_error()
{
    return (triplet){-9, -1, 0, false};
}

char is_error(triplet t)
{
    return t.count == -9;
}

void assert_triplet(triplet t)
{
    assert(is_error(t) == 0);
}

triplet_store *make_store(int size)
{
    triplet_store *s = malloc(sizeof(triplet_store));
    s->tail = 0;
    s->head = 0;
    s->capacity = size;
    s->triplets = malloc(sizeof(triplet) * size);
    return s;
}

void free_store(triplet_store *s)
{
    free(s->triplets);
    free(s);
}

int store_sizeof(triplet_store *s)
{
    int count = (s->head - s->tail + 1);
    if (count <= 0)
        count += s->capacity;
    return count;
}

triplet store_push(triplet_store *s, triplet t)
{
    assert(t.startingIndex != 0);
    assert(store_sizeof(s) <= s->capacity);
    s->triplets[s->head] = t;
    s->head = (s->head + 1) % s->capacity;
    return t;
}

triplet store_pop(triplet_store *s)
{
    assert(store_sizeof(s) > 0);
    triplet result = s->triplets[s->tail];
    s->tail = (s->tail + 1) % s->capacity;
    return result;
}
