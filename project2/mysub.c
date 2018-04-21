#include <stdio.h>

void set_A(int A[], int element)
{
    if (A[1] == -1)
        A[1] = element;
    else if (A[2] == -1)
        A[2] = element;
}

int find_A_from_ABB(int A[]);
int find_A_from_AAB(int A[]);

int predict_singleton(int A[], int *B, int current)
{
    int indices[4] = {A[0], A[1], *B, current};
    int count = QCOUNT(1, indices);

    switch (count)
    {
    case 2:
        return 1;
    case 0:
        return -1;
    // Invalid cases
    default:
        return -7;
    }
}

int predict_pair(int A[], int *B, int current)
{
    int indices[4] = {A[0], A[1], current, current + 1};
    int count = QCOUNT(1, indices);

    switch (count)
    {
    case 0:
        return -2;
    case 2:
        return 0;
    case 4:
        return 2;
    // Invalid cases
    default:
        return -7;
    }
}

int determine_hard_triplet(int A[], int *B, int current, int max, int *firstTriplet)
{
    if (*B == -1)
    {
        int indices[4] = {2, 3, 4, current};
        int count = QCOUNT(1, indices);

        indices[3] = current + 1;
        int count2 = QCOUNT(1, indices);

        switch (*firstTriplet)
        {
        case 0:
            switch (count)
            {
            case 0: // A
                set_A(A, current);
                break; // AAB
            case 2: // B
                *B = current; // AAB or BBB
                break;
            default:
                return -7; // Error
            }

            switch (count2)
            {
            case 0: // A
                set_A(A, current + 1);
                if (count != 2)
                    *B = current + 2; // AAB
                return 1;
            case 2: // B
                *B = current + 1;
                if (count == 0) // ABA
                {
                    set_A(A, current + 2);
                    return 1;
                }
                else            // BBB
                    return -3;
            default:
                return -7; // Error
            }
            break;

        case 2:
        {
            int result = 0;
            switch (count)
            {
            case 2: // A
                set_A(A, current);
                break; // AAB
            case 0: // B
            case 4: // B
                *B = current; // AAB or BBB
                break;
            default:
                return -7; // Error
            }

            switch (count2)
            {
            case 2: // A
                set_A(A, current + 1);
                if (count == 2) // Got A previously
                    *B = current + 2; // AAB
                else
                    set_A(A, current + 2);
                result = 1;
                break;
            case 0: // B
            case 4: // B
                *B = current + 1;
                if (count == 0) // ABA
                {
                    set_A(A, current + 2);
                    return 1;
                }
                else            // BBB
                    result = -3;
                break;
            default:
                return -7; // Error
            }

            // Add on the result of calculating firstIndex's state
            indices[3] = *B;
            int count3 = QCOUNT(1, indices);
            switch (count3)
            {
            case 0: // AAB
                return result + 1;
            case 4: // BBB
                return result - 3;
            default:
                return -7;
            }
            break;
        }

        case 4:
            switch (count)
            {
            case 4: // A
                set_A(A, current);
                break; // AAB or ABA
            case 2: // B
                *B = current; // BAA or BBB
                break;
            default:
                return -7; // Error
            }

            switch (count2)
            {
            case 4: // A
                set_A(A, current + 1);
                if (count != 2)
                    *B = current + 2;
                return 1;
            case 2: // B
                *B = current + 1;
                if (count == 0) // ABA
                {
                    set_A(A, current + 2);
                    return 1;
                }
                else            // BBB
                    return -3;
            default:
                return -7; // Error
            }
            break;

        default:
            return -7;
        }
    }
    else
    {
        int indices[4] = {*B, current, current + 1, current + 2};
        int count = QCOUNT(1, indices);
        switch (count)
        {
        case 0: // AAB
            // TODO keep track of AAB-tuples
            return 1;
        case 4: // BBB
            return -3;
        default:
            return -7;
        }
    }
}

int predict_triplet(int A[], int *B, int current, int max, int *firstTriplet)
{
    int leftover = max - current;

    if (leftover == 0)
        return predict_singleton(A, B, current);
    else if (leftover == 1)
        return predict_pair(A, B, current);

    int indices[4] = {A[0], current, current + 1, current + 2};
    int count = QCOUNT(1, indices);

    if (*firstTriplet == -7)
    {
        *firstTriplet = count;
        if (count == 2)
            return 0;
    }

    switch (count)
    {
    case 0: // ABB
        // TODO keep track of ABB-tuples
        return -1;
    case 2: // BBB or AAB
        return determine_hard_triplet(A, B, current, max, firstTriplet);
    case 4: // AAA
        A[1] = current;
        A[2] = current + 1;
        return 3;
    default:
        printf("Error: QCOUNT passed erroneous input: index = [ %d, %d, %d, %d]",
            indices[0], indices[1], indices[2], indices[3]);
        return -7;
    }
}

int mysub(int n)
{
    int A[3] = {1, -1, -1};
    int B = -1;

    int firstTriplet = -7;
    int count = predict_triplet(A, &B, 2, n, &firstTriplet);

    for (int i = 5; i <= n; i += 3)
    {
        // Early stop
        if (count > n - i)
            break;

        int result = predict_triplet(A, &B, i, n, &firstTriplet);
        if (result < -6)
            return -1;

        count += result;
    }

    if (count > 0)
        return A[0];
    else if (count < 0)
        return B;

    return 0;
}
