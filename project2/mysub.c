// mysub.h

#include <assert.h>
#include <stdlib.h>

// Main function. Takes number of elements as input and outputs an index of the
// majority class.
int mysub(int n);

// Sets A in the next available space.
void set_A(int A[], int value);

// Sets B in the next available space.
void set_B(int *B, int value);

// Find the identity of two sets that evaluated as fours.
// Takes 0.5 queries per quad
int consider_fours(int A[], int *B, int firstSet, int secondSet);

// Find the identity of a single four.
// Takes 1 query per quad
int consider_single_four(int A[], int *B, int set);

// Find the identity of a single two.
// Takes 1-2 queries per quad
int consider_single_two(int A[], int *B, int set);

// Calculate the result based on our stored information.
int calculate_result(int A[], int *B, int count);

// Find the identify of the final three elements.
// Takes 1-2 queries
int consider_final_three(int A[], int *B, int n, int zero, int *twos, int numTwos);

// Calculate the result knowing it depends on the final three indices.
// Takes 1 query
int consider_final_two(int A[], int *B, int n);

// Calculate the result knowing it depends on the final three indices.
// Takes 1 query
int consider_final_one(int A[], int *B, int n);

// Find an instance of A.
void search_for_A(int A[], int *B, int zero, int twos[], int numTwos);

// Find instances of A and B for further calculations.
void search_for_B(int A[], int *B, int zero, int twos[], int numTwos);

// END mysub.h


// mysub.c

int mysub(int n)
{
    // We will have floor(n/4) quads in total.
    int numQuads = n/4;

    // Initialize the first entry in the array to class A.
    int A[3] = {1, -1, -1};

    // We need to keep track of a single B.
    int *B = malloc(sizeof(int));
    *B = -1;

    // We need to count the number of uncalculated elements.
    int remaining = n - 1;

    // We need to keep track of all of the fours and twos. Here we decide to use
    // the starting index of each quad for tracking.
    int *fours = malloc(numQuads * sizeof(int));
    int *twos  = malloc(numQuads * sizeof(int));
    int numFours = 0;
    int numTwos  = 0;

    // Let's also keep track of one zero for edge cases.
    int zero = -1;

    // First, let's classify each quad.
    for (int i = 2; i < n - 2; i += 4)
    {
        int indices[4] = {i, i+1, i+2, i+3};
        int result = QCOUNT(1, indices);
        switch (result)
        {
        case 4:
            fours[numFours] = i;
            numFours++;
            break;
        case 2:
            twos[numTwos] = i;
            numTwos++;
            break;
        case 0:
            zero = i;
            remaining -= 4;
            break;
        default:
            printf("Error: QCOUNT called with incorrect indices.\n");
            abort();
        }
    }

    // Each quad is now classified, moving onto evaluation of 4's and 2's
    int count = 1; // number of A's - number of B's, starting with index 1 being A
    int maxSwing = 4*numFours + 2*numTwos + ((n - 1) % 4); // number of elements unaccounted for

    // We start with fours since they require the lowest number of comparisons.
    for (int i = 0; numFours > 0;)
    {
        if (numFours == 1 || A[1] == -1)
        {
            count += consider_single_four(A, B, fours[i]);
            remaining -= 4;
            maxSwing -= 4;
            numFours--;
            i++;
        }
        else
        {
            count += consider_fours(A, B, fours[i], fours[i+1]);
            remaining -= 8;
            maxSwing -= 8;
            numFours -= 2;
            i += 2;
        }

        // Check if we should stop early.
        int absCount = count > 0 ? count : -count;
        if (absCount > remaining || maxSwing < absCount)
        {
            if (count < 0 && *B == -1)
                search_for_B(A, B, zero, twos, numTwos);
            return calculate_result(A, B, count);
        }
    }

    // Next, we calculate twos.
    for (int i = 0; i < numTwos; i++)
    {
        count += consider_single_two(A, B, twos[i]);
        remaining -= 4;
        maxSwing -= 2;

        // Check if we should stop early.
        int absCount = count > 0 ? count : -count;
        if (absCount > remaining || maxSwing < absCount)
        {
            if (count < 0 && *B == -1)
                search_for_B(A, B, zero, twos, numTwos);
            return calculate_result(A, B, count);
        }
    }

    // Finally, we calculate the last few values.
    switch (remaining)
    {
    case 3:
        count += consider_final_three(A, B, n, zero, twos, numTwos);
        break;
    case 2:
        if (A[1] == -1)
            search_for_A(A, B, zero, twos, numTwos);
        count += consider_final_two(A, B, n);
    case 1:
        if (A[1] == -1)
            search_for_A(A, B, zero, twos, numTwos);
        if (A[2] == -1)
            search_for_A(A, B, zero, twos, numTwos);
        count += consider_final_one(A, B, n);
    case 0:
        break;
    default:
        printf("Error: remainder not in bounds 4 > x => 0.\n");
        abort();
    }

    if (count < 0 && *B == -1)
        search_for_B(A, B, zero, twos, numTwos);
    return calculate_result(A, B, count);
}

void set_A(int A[], int value)
{
    if (A[1] == value)
        return;
    if (A[2] == value)
        return;

    if (A[1] == -1)
        A[1] = value;
    else if (A[2] == -1)
        A[2] = value;
}

void set_B(int *B, int value)
{
    if (*B == -1)
        *B = value;
}

int consider_fours(int A[], int *B, int firstSet, int secondSet)
{
    int indices[4] = {A[0], A[1], firstSet, secondSet};
    int result = QCOUNT(1, indices);
    switch (result)
    {
    case 4:
        return 8;
    case 2:
        return 0;
    case 0:
        set_B(B, firstSet);
        return -8;
    default:
        printf("Error: QCOUNT called with incorrect indices.\n");
        abort();
    }
}

int consider_single_four(int A[], int *B, int set)
{
    int indices[4] = {A[0], set, set+1, set+2};
    switch (QCOUNT(1, indices))
    {
    case 4:
        A[1] = set;
        A[2] = set + 1;
        return 4;
    case 2:
        *B = set;
        return -4;
    default:
        printf("Error: QCOUNT called with incorrect indices.\n");
        abort();
    }
}

int consider_single_two(int A[], int *B, int set)
{
    int indices[4] = {A[0], set, set+1, set+2};
    int result = QCOUNT(1, indices);
    switch (result)
    {
    case 4:
        return 2; // AAAB
    case 2:
        indices[1] = set + 3;
        if (QCOUNT(1, indices) == 0)
            return -2; // BBBA
        else
            return 2;  // AAAB
    case 0:
        return -2; // BBBA
    default:
        printf("Error: QCOUNT called with incorrect indices.\n");
        abort();
    }
}

int calculate_result(int A[], int *B, int count)
{
    if (count > 0)
        return A[0];
    else if (count < 0)
        return *B;
    else
        return 0;
}

int consider_final_three(int A[], int *B, int n, int zero, int *twos, int numTwos)
{
    int indices[4] = {A[0], n-2, n-1, n};
    int result = QCOUNT(1, indices);
    switch (result)
    {
    case 4:
        return 3;
    case 2:
        if (A[1] == -1)
            search_for_A(A, B, zero, twos, numTwos);
        indices[1] = A[1];
        return (QCOUNT(1, indices) == 0) ? -3 : 1;
    case 0:
        return -1;
    default:
        printf("Error: QCOUNT called with incorrect indices.\n");
        abort();
    }
}

int consider_final_two(int A[], int *B, int n)
{
    int indices[4] = {A[0], A[1], n-1, n};
    int result = QCOUNT(1, indices);
    switch (result)
    {
    case 4:
        return 2;
    case 2:
        return 0;
    case 0:
        return -2;
    default:
        printf("Error: QCOUNT called with incorrect indices.\n");
        abort();
    }
}

int consider_final_one(int A[], int *B, int n)
{
    int indices[4] = {A[0], A[1], A[2], n};
    return (QCOUNT(1, indices) == 4) ? 1 : -1;
}

void search_for_A_in_two(int A[], int *B, int two)
{
    int indices[4] = {A[0], two, two+1, two+2};
    int result = QCOUNT(1, indices);
    switch (result)
    {
    case 2: // BAAA, AABA, ABAA, BAAA
        set_A(A, two + 3);
        break;
    case 4: // AAAB
        set_A(A, two + 1);
        set_A(A, two + 2);
        set_B(B, two + 3);
        break;
    case 0: // BBAB, BABB, ABBB
        set_B(B, two + 3);
        indices[3] = *B;
        result = QCOUNT(1, indices);
        switch (result)
        {
        case 2: // BBAB
            set_A(A, two + 2);
            break;
        case 0: // BABB, ABBB
            indices[2] = two + 2;
            result = QCOUNT(1, indices);
            switch (result)
            {
            case 0: // ABBB
                set_A(A, two);
                break;
            case 2: // BABB
                set_A(A, two+1);
                break;
            default:
                abort();
            }
            break;
        default:
            abort();
        }
        break;
    default:
        abort();
    }
}

void search_for_A_in_zero(int A[], int *B, int zero)
{
    int indices[4] = {A[0], zero, zero+1, zero+2};
    int result = QCOUNT(1, indices);
    switch (result)
    {
    case 0: // BBAA, BABA, ABBA
        set_A(A, zero + 3);
        break;
    case 2: // BAAB, AABB, ABAB
        set_B(B, zero + 3);
        indices[3] = *B;
        int result = QCOUNT(1, indices);
        switch (result)
        {
        case 0: // BAAB, ABAB
            set_A(A, zero + 2);
            break;
        case 2: // AABB
            set_A(A, zero);
            set_A(A, zero + 1);
            break;
        default:
            abort();
        }
        break;
    default:
        abort();
    }
}

void search_for_A(int A[], int *B, int zero, int twos[], int numTwos)
{
    if (zero != -1)
        search_for_A_in_zero(A, B, zero);
    else
        search_for_A_in_two(A, B, twos[numTwos - 1]);
}

void search_for_B_in_two(int A[], int *B, int two)
{
    int indices[4] = {A[0], two, two+1, two+2};
    int result = QCOUNT(1, indices);
    switch (result)
    {
    case 2: // BBBA, AABA, ABAA, BAAA
        set_A(A, two + 3);
        indices[3] = two + 3;
        result = QCOUNT(1, indices);
        switch (result)
        {
        case 4: // AABA
            set_A(A, two + 1);
            set_B(B, two + 2);
            break;
        case 0: // BBBA, ABAA, BAAA
            indices[2] = two + 2;
            result = QCOUNT(1, indices);
            switch (result)
            {
            case 0: // BBBA
                set_B(B, two + 2);
                break;
            case 4: // AABA
                set_A(A, two + 1);
                set_B(B, two + 2);
                break;
            case 2: // ABAA, BAAA
                set_A(A, two + 2);
                indices[2] = two + 2;
                result = QCOUNT(1, indices);
                switch (result)
                {
                case 4: // ABAA
                    set_B(B, two + 1);
                    break;
                case 2: // BAAA
                    set_B(B, two);
                    break;
                default:
                    abort();
                }
                break;
            default:
                abort();
            }
            break;
        default:
            abort();
        }
        break;
    case 4: // AAAB
        set_A(A, two + 1);
        set_A(A, two + 2);
        set_B(B, two + 3);
        break;
    case 0: // BBAB, BABB, ABBB
        set_B(B, two + 3);
        break;
    default:
        abort();
    }
}

void search_for_B_in_zero(int A[], int *B, int zero)
{
    int indices[4] = {A[0], zero, zero+1, zero+2};
    int result = QCOUNT(1, indices);
    switch (result)
    {
    case 2: // BAAB, AABB, ABAB
        set_B(B, zero + 3);
        break;
    case 0: // BBAA, BABA, ABBA
        set_A(A, zero + 3);
        indices[3] = zero + 3;
        int result = QCOUNT(1, indices);
        switch (result)
        {
        case 0: // BABA, ABBA
            set_B(B, zero + 1);
            break;
        case 2: // BBAA
            set_B(B, zero + 1);
            set_A(A, zero + 2);
            break;
        default:
            abort();
        }
        break;
    default:
        abort();
    }
}

void search_for_B(int A[], int *B, int zero, int twos[], int numTwos)
{
    if (zero != -1)
        search_for_B_in_zero(A, B, zero);
    else
        search_for_B_in_two(A, B, twos[numTwos - 1]);
}

// END mysub.c
