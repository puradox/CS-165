#include <assert.h>
#include "mysub.h"
#include "perf.h"

// Predict the first triplet, which is either AAB or ABA or BAA or BBB.
// Only called with there is no B, which means all triplets were
// either ABB or AAA.
triplet predict_first(int A[], int *B) // 1-3 queries
{
    if (A[1] == -1)
        find(A, B); // 1-2 queries

    int indices[4] = {A[0], A[1], 2, 3};
    int count = QCOUNT(1, indices);
    assert(count >= 0);

    switch (count)
    {
    case 0: // BBB (25%)
        *B = 2;
        return (triplet){-3, 2, 3, true};
    case 2: // ABA or BAA (50%)
        return (triplet){1, 2, 3, true};
    case 4: // AAB (25%)
        set_A(A, 2);
        set_A(A, 3);
        *B = 4;
        return (triplet){1, 2, 3, true};
    default:
        return make_error();
    }
}

triplet predict_singleton(int A[], int *B, int current) // 1-3 query
{
    if (A[1] == -1) // TODO: Does this always happen?
        find(A, B); // 1-2 queries

    if (A[2] != -1)
        return predict_singleton_with_AA(A, B, current); // 1 query
    if (*B != -1)
        return predict_singleton_with_AB(A, B, current); // 1 query

    return make_error();
}

triplet predict_singleton_with_AA(int A[], int *B, int current) // 1 query
{
    int indices[4] = {A[0], A[1], A[2], current}; // AAAX
    int count = QCOUNT(1, indices);
    assert(count >= 0);

    switch (count)
    {
    case 2: // B
        *B = current;
        return make_singleton(-1, current);
    case 4: // A
        return make_singleton(1, current);
    default:
        return make_error();
    }
}

triplet predict_singleton_with_AB(int A[], int *B, int current) // 1 query
{
    int indices[4] = {A[0], A[1], *B, current}; // AABX
    int count = QCOUNT(1, indices);
    assert(count >= 0);

    switch (count)
    {
    case 0: // B
        return make_singleton(-1, current);
    case 2: // A
        return make_singleton(1, current);
    default:
        return make_error();
    }
}

triplet predict_pair(int A[], int *B, int current) // 1-3 queries
{
    if (A[1] == -1)
        find(A, B); // 1-2 queries

    assert(A[1] != -1);

    int indices[4] = {A[0], A[1], current, current + 1}; // AAXX
    int count = QCOUNT(1, indices);
    assert(count >= 0);

    switch (count)
    {
    case 0: // BB
        *B = current;
        return make_pair(-2, current);
    case 2: // AB or BA
        return make_pair(0, current);
    case 4: // AA
        set_A(A, current);
        set_A(A, current + 1);
        return make_pair(2, current);
    default:
        return make_error();
    }
}

// Reach a "hard" triplet of AAB or ABA or BAA or BBB without finding a B
triplet determine_hard_triplet_without_B(int A[], int *B, int current, triplet *first)
{
    int indices[4] = {2, 3, 4, current};
    int count = QCOUNT(1, indices);
    assert(count >= 0);

    indices[3] = current + 1;
    int count2 = QCOUNT(1, indices);
    assert(count2 >= 0);

    switch (first->count)
    {
    case -1: // First triplet: ABB or BAB or BBA
        // count = 0 when A
        // count = 2 when B

        if (count == 0 && count2 == 0) // AAB
        {
            set_A(A, current);
            set_A(A, current + 1);
            *B = current + 2;
            return make_triplet(1, current);
        }
        else if (count == 0 && count2 == 2) // ABA
        {
            set_A(A, current);
            set_A(A, current + 2);
            *B = current + 1;
            return make_triplet(1, current);
        }
        else if (count == 2 && count2 == 0) // BAA
        {
            set_A(A, current + 1);
            set_A(A, current + 2);
            *B = current;
            return make_triplet(1, current);
        }
        else if (count == 2 && count2 == 2) // BBB
        {
            *B = current;
            return make_triplet(-3, current);
        }
        else
            return make_error();

    case 0: // First triplet: AAB or ABA or BAA or BBB
        // count = 2      when A
        // count = 0 or 4 when B
    {
        triplet result;

        if (count == 2 && count2 == 2) // AAB
        {
            set_A(A, current);
            set_A(A, current + 1);
            *B = current + 2;
            result = make_triplet(1, current);
        }
        else if (count == 2 && (count2 == 0 || count2 == 4)) // ABA
        {
            set_A(A, current);
            set_A(A, current + 2);
            *B = current + 1;
            result = make_triplet(1, current);
        }
        else if ((count == 0 || count == 4) && count2 == 2) // BAA
        {
            set_A(A, current + 1);
            set_A(A, current + 2);
            *B = current;
            result = make_triplet(1, current);
        }
        else if ((count == 0 || count == 4) && (count2 == 0 || count2 == 4)) // BBB
        {
            *B = current;
            result = make_triplet(-3, current);
        }
        else
            return make_error();

        // Find the first triplet's value
        triplet result2 = determine_hard_triplet(A, B, 2, first);
        first->count = result2.count;
        first->accountedFor = true;

        // Return the final count without adding it to the global stores.
        return (triplet){result.count + result2.count, current, 3, 1};
    }

    case 3: // AAA
        // count = 4 when A
        // count = 2 when B

        if (count == 4 && count2 == 4) // AAB
        {
            set_A(A, current);
            set_A(A, current + 1);
            *B = current + 2;
            return make_triplet(1, current);
        }
        else if (count == 4 && count2 == 2) // ABA
        {
            set_A(A, current);
            set_A(A, current + 2);
            *B = current + 1;
            return make_triplet(1, current);
        }
        else if (count == 2 && count2 == 4) // BAA
        {
            set_A(A, current + 1);
            set_A(A, current + 2);
            *B = current;
            return make_triplet(1, current);
        }
        else if (count == 2 && count2 == 2) // BBB
        {
            *B = current;
            return make_triplet(-3, current);
        }
        else // Error
            return make_error();

    default: // Error
        return make_error();
    }
}

// Reach a "hard" triplet of AAB or ABA or BAA or BBB
triplet determine_hard_triplet(int A[], int *B, int current, triplet *first)
{
    if (*B == -1)
        return determine_hard_triplet_without_B(A, B, current, first);

    int indices[4] = {*B, current, current + 1, current + 2}; // BXXX
    int count = QCOUNT(1, indices);

    switch (count)
    {
    case 0: // AAB or ABA or BAA
        return make_triplet(1, current);
    case 4: // BBB
        return make_triplet(-3, current);
    default: // Error
        return make_error();
    }
}

triplet predict_triplet(int A[], int *B, int current, triplet *first)
{
    int indices[4] = {A[0], current, current + 1, current + 2};
    int count = QCOUNT(1, indices);
    assert(count >= 0);

    if (first == 0 && count == 2) // first prediction + hard = cannot determine
        return make_first_hard();

    switch (count)
    {
    case 0: // ABB or BAB or BBA
        return make_triplet(-1, current);
    case 2: // AAB or ABA or BAA or BBB
        inc_triplet_hard();
        return determine_hard_triplet(A, B, current, first);
    case 4: // AAA
        A[1] = current;
        A[2] = current + 1;
        return make_triplet(3, current);
    default: // Error
        return make_error();
    }
}

int mysub(int n)
{
    int A[3] = {1, -1, -1};
    int B = -1;
    int count = 1;

    inc_mysub();
    store_AAB = make_store((n - 1) / 3);
    store_ABB = make_store((n - 1) / 3);

    triplet first = predict_triplet(A, &B, 2, (triplet *)0);
    assert_triplet(first);
    count += first.count;

    for (int i = 5; i <= n;)
    {
        int leftover = n - i + 1;

        // Early stop without counting first triplet
        if (!first.accountedFor)
        {
            // First triplet not counted yet, it was a "hard" triplet
            // 75% of the time it will be +1 (AAB)
            // 25% of the time it will be -3 (BBB)

            // Does the first triplet not matter?
            if (count > leftover + 3 || count < -leftover - 1)
            {
                inc_early_stop();
                break;
            }

            // Chances are the first triplet is not -3 (BBB)
            // Double down on the stats. Take the win 75% of the time.
            if (count > leftover)
            {
                first = predict_first(A, &B);
                assert_triplet(first);
                count += first.count;
            }
        }

        // Early stop
        if (first.accountedFor)
        {
            if (count > leftover || count < -leftover)
            {
                inc_early_stop();
                break;
            }
        }

        triplet result;

        if (leftover == 1)
        {
            inc_singleton();
            result = predict_singleton(A, &B, i);
            i += 1;
        }
        else if (leftover == 2 || A[1] != -1)
        {
            inc_pair();
            result = predict_pair(A, &B, i);
            i += 2;
        }
        else
        {
            inc_triplet();
            result = predict_triplet(A, &B, i, &first);
            i += 3;
        }

        assert_triplet(result);
        count += result.count;
    }

    // Check if the first triplet was unaccounted for and the difference matters.
    // 75% of the time it will be +1 (ABB)
    // 25% of the time it will be -3 (BBB)
    if (!first.accountedFor && count >= -1 && count <= 3)
    {
        first = predict_first(A, &B);
        assert_triplet(first);
        count += first.count;
    }

    int answer;

    if (count < 0)
    {
        if (B == -1)
            find(A, &B);
        return B;
    }
    else if (count > 0)
        answer = A[0];
    else
        answer = 0;

    free_store(store_AAB);
    free_store(store_ABB);

    return answer;
}
