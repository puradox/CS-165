#include <assert.h>
#include "find.h"
#include "perf.h"

void set_A(int A[], int element)
{
    assert(element >= 1);

    for (int i = 0; i < 3; i++)
        assert(A[i] != element); // Duplicate?

    if (A[1] == -1)
        A[1] = element;
    else if (A[2] == -1)
        A[2] = element;
}

int find(int A[], int *B)
{
    inc_find();
    assert(!(A[1] != -1 && A[2] != -1 && *B != -1)); // Unnecessary?
    int current;
    int result = -1;

    // Different priorities based on whether there's B.
    if (*B == -1)
    {
        if (store_sizeof(store_ABB) > 0)
        {
            current = store_pop(store_ABB).startingIndex;
            result = find_from_ABB(A, B, current);
        }
        else if (store_sizeof(store_AAB) > 0)
        {
            current = store_pop(store_AAB).startingIndex;
            result = find_from_AAB(A, B, current);
        }
    }
    else
    {
        if (store_sizeof(store_AAB) > 0)
        {
            current = store_pop(store_AAB).startingIndex;
            result = find_from_AAB(A, B, current);
        }
        else if (store_sizeof(store_ABB) > 0)
        {
            current = store_pop(store_ABB).startingIndex;
            result = find_from_ABB(A, B, current);
        }
    }

    assert(result != -1);
    return result;
}

int find_from_AAB(int A[], int *B, int current) // (1-2 queries)
{
    if (A[1] != -1 && A[2] != -1 && *B == -1)         // find B
        return find_from_AAB_with_AAA(A, B, current); // (1-2 queries)
    if (A[1] != -1 && A[2] == -1 && *B != -1)         // find A
        return find_from_AAB_with_AAB(A, B, current); // (1 query)
    if (A[1] != -1 && A[2] == -1 && *B == -1)         // find A and B
        return find_from_AAB_with_AA(A, B, current);  // (1-2 queries)
    if (A[1] == -1 && A[2] == -1 && *B != -1)         // find two As
        return find_from_AAB_with_AB(A, B, current);  // (1-2 queries)

    return -1;
}

int find_from_AAB_with_AAA(int A[], int *B, int current) // 1-2 query
{
    int indices[4] = {A[0], A[1], current, current + 1};
    int count1 = QCOUNT(1, indices);
    assert(count1 >= 0);

    switch (count1)
    {
    case 4: // AAB
        *B = current + 3;
        return 0;
    case 2: // ABA or BAA
        break;
    default:
        return -1;
    }

    indices[2] = current + 1;
    indices[3] = current + 2;
    int count2 = QCOUNT(1, indices);

    switch (count2)
    {
    case 4: // BAA
        *B = current;
        return 0;
    case 2: // ABA
        *B = current + 1;
        return 0;
    default:
        return -1;
    }
}

int find_from_AAB_with_AAB(int A[], int *B, int current) // 1 query
{
    int indices[4] = {A[0], A[1], *B, current};
    int count = QCOUNT(1, indices);
    assert(count >= 0);

    switch (count)
    {
    case 2: // AAB or ABA
        set_A(A, current);
        return 0;
    case 4: // BAA
        set_A(A, current + 1);
        set_A(A, current + 2);
        return 0;
    default:
        return -1;
    }
}

int find_from_AAB_with_AA(int A[], int *B, int current) // 1-2 queries
{
    int indices[4] = {A[0], A[1], current, current + 1};
    int count1 = QCOUNT(1, indices);
    assert(count1 >= 0);

    switch (count1)
    {
    case 4: // AAB
        set_A(A, current);
        set_A(A, current + 1);
        *B = current + 3;
        return 0;
    case 2: // ABA or BAA
        break;
    default:
        return -1;
    }

    indices[2] = current + 1;
    indices[3] = current + 2;
    int count2 = QCOUNT(1, indices);
    assert(count2 >= 0);

    switch (count2)
    {
    case 4: // BAA
        set_A(A, current + 1);
        set_A(A, current + 2);
        *B = current;
        return 0;
    case 2: // ABA
        set_A(A, current);
        set_A(A, current + 2);
        *B = current + 3;
        return 0;
    default:
        return -1;
    }
}

int find_from_AAB_with_AB(int A[], int *B, int current) // 1-2 queries
{
    int indices[4] = {A[0], *B, current, current + 1};
    int count1 = QCOUNT(1, indices);
    assert(count1 >= 0);

    switch (count1)
    {
    case 2: // AAB
        set_A(A, current);
        set_A(A, current + 1);
        return 0;
    case 0: // ABA or BAA
        break;
    default:
        return -1;
    }

    indices[2] = current + 1;
    indices[3] = current + 2;
    int count2 = QCOUNT(1, indices);
    assert(count2 >= 0);

    switch (count2)
    {
    case 2: // BAA
        set_A(A, current + 1);
        set_A(A, current + 2);
        return 0;
    case 0: // ABA
        set_A(A, current);
        set_A(A, current + 2);
        return 0;
    default:
        return -1;
    }
}

int find_from_ABB(int A[], int *B, int current) // 1-2 queries
{
    if (A[1] != -1 && A[2] != -1 && *B == -1)         // find B
        return find_from_ABB_with_AAA(A, B, current); // (1 query)
    if (A[1] != -1 && A[2] == -1 && *B != -1)         // find A
        return find_from_ABB_with_AAB(A, B, current); // (1-2 queries)
    if (A[1] != -1 && A[2] == -1 && *B == -1)         // find A and B
        return find_from_ABB_with_AA(A, B, current);  // (1-2 queries)
    if (A[1] == -1 && A[2] == -1 && *B != -1)         // find two As
        return find_from_ABB_with_AB(A, B, current);  // (1-2 queries)

    int current2 = store_pop(store_ABB).startingIndex;
    return find_from_two_ABBs(A, B, current, current2);
}

int find_from_ABB_with_AAA(int A[], int *B, int current) // 1 query
{
    int indices[4] = {A[0], A[1], A[2], current};
    int count = QCOUNT(1, indices);
    assert(count >= 0);

    switch (count)
    {
    case 4: // ABB
        set_A(A, current);
        *B = current + 1;
        return 0;
    case 2: // BBA or BAB
        *B = current;
        return 0;
    default:
        return -1;
    }
}

int find_from_ABB_with_AAB(int A[], int *B, int current) // 1-2 queries
{
    int indices[4] = {A[0], A[1], *B, current};
    int count1 = QCOUNT(1, indices);
    assert(count1 >= 0);

    switch (count1)
    {
    case 2: // ABB
        set_A(A, current);
        return 0;
    case 4: // BBA or BAB
        break;
    default:
        return -1;
    }

    indices[3] = current + 1;
    int count2 = QCOUNT(1, indices);
    assert(count2 >= 0);

    switch (count2)
    {
    case 2: // BAB
        set_A(A, current + 1);
        return 0;
    case 4: // BBA
        set_A(A, current + 2);
        return 0;
    default:
        return -1;
    }
}

int find_from_ABB_with_AA(int A[], int *B, int current) // 1-2 queries
{
    int indices[4] = {A[0], A[1], current, current + 1};
    int count1 = QCOUNT(1, indices);
    assert(count1 >= 0);

    switch (count1)
    {
    case 0: // BBA
        set_A(A, current + 2);
        *B = current;
        return 0;
    case 2: // ABB or BAB
        break;
    default:
        return -1;
    }

    indices[2] = current + 1;
    indices[3] = current + 2;
    int count2 = QCOUNT(1, indices);
    assert(count2 >= 0);

    switch (count2)
    {
    case 0: // ABB
        set_A(A, current);
        *B = current + 1;
        return 0;
    case 2: // BAB
        set_A(A, current + 1);
        *B = current;
        return 0;
    default:
        return -1;
    }
}

int find_from_ABB_with_AB(int A[], int *B, int current) // 1-2 queries
{
    int indices[4] = {A[0], *B, current, current + 1};
    int count1 = QCOUNT(1, indices);
    assert(count1 >= 0);

    switch (count1)
    {
    case 2: // BBA
        set_A(A, current + 2);
        return 0;
    case 0: // ABB or BAB
        break;
    default:
        return -1;
    }

    indices[2] = current + 1;
    indices[3] = current + 2;
    int count2 = QCOUNT(1, indices);
    assert(count2 >= 0);

    switch (count2)
    {
    case 2: // ABB
        set_A(A, current);
        return 0;
    case 0: // BAB
        set_A(A, current + 1);
        return 0;
    default:
        return -1;
    }
}

int find_from_two_ABBs(int A[], int *B, int left, int right)
{
    int indices[4] = {left, left + 1, right, right + 1};
    int count1 = QCOUNT(1, indices);
    int count2, count3;

    switch (count1)
    {
    case 4: // BBA BBA (1/9)
        set_A(A, left + 2);
        set_A(A, right + 2);
        *B = left;
        return 0;
    case 2: // XXX BBA or BBA XXX (4/9)
        // XXX BBA - ABB BBA or BAB BBA
        // BBA XXX - BBA ABB or BBA BAB
        indices[2] = right + 1;
        indices[3] = right + 2;
        count2 = QCOUNT(1, indices);

        switch (count2)
        {
        case 4: // BBA ABB
            set_A(A, left + 2);
            set_A(A, right);
            *B = left;
            return 0;
        case 2: // BBA BAB
            set_A(A, left + 2);
            set_A(A, right + 1);
            *B = left;
            return 0;
        case 0: // ABB BBA or BAB BBA
            indices[0] = left + 1;
            indices[1] = left + 2;
            count3 = QCOUNT(1, indices);

            switch (count3)
            {
            case 2: // ABB BBA
                set_A(A, left);
                set_A(A, right + 2);
                *B = left + 1;
                return 0;
            case 0: // BAB BBA
                set_A(A, left + 1);
                set_A(A, right + 2);
                *B = left;
                return 0;
            default:
                return -1;
            }
        default:
            return -1;
        }
    case 0: // ABB XXX or BAB XXX (4/9)
        // ABB XXX - ABB ABB or ABB BAB
        // BAB XXX - BAB ABB or BAB BAB
        indices[0] = left + 1;
        indices[1] = left + 2;
        indices[2] = right + 1;
        indices[3] = right + 2;
        count2 = QCOUNT(1, indices);

        switch (count2)
        {
        case 4: // ABB ABB
            set_A(A, left);
            set_A(A, right);
            *B = left + 1;
            return 0;
        case 0: // BAB BAB
            set_A(A, left + 1);
            set_A(A, right + 1);
            *B = left;
            return 0;
        case 2: // ABB BAB or BAB ABB
            indices[0] = left + 0;
            count3 = QCOUNT(1, indices);

            switch (count3)
            {
            case 4: // BAB ABB
                set_A(A, left + 1);
                set_A(A, right);
                *B = left;
                return 0;
            case 0: // ABB BAB
                set_A(A, left);
                set_A(A, right + 1);
                *B = left + 1;
                return 0;
            default:
                return -1;
            }
        default:
            return -1;
        }
    default:
        return -1;
    }
}
