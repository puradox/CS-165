#include <stdio.h>

int predict_singleton(int A[], int *B, int current)
{
    int indices[4] = {A[0], A[1], A[3], current};
    int count = QCOUNT(1, indices);

    switch (count)
    {
    case 2:
        return -1;
    case 4:
        return 1;
    // Invalid cases
    case 0:
        return -5;
    default:
        return -5;
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
        return -5;
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
                break; // Must be in state AAB
            case 2: // B
                *B = current; // Could be in AAB or BBB
                break;
            default:
                return -5; // Error
            }

            switch (count2)
            {
            case 0: // A
                if (count != 2)
                    *B = current + 2; // Must be in state AAB
                return 1;
            case 2: // B
                *B = current + 1;
                if (count == 0) // AAB
                    return 1;
                else            // BBB
                    return -3;
            default:
                return -5; // Error
            }
        case 2:
            int result = 0;
            switch (count)
            {
            case 2: // A
                break; // Must be in state AAB
            case 0: // B
            case 4: // B
                *B = current; // Could be in AAB or BBB
                break;
            default:
                return -5; // Error
            }

            switch (count2)
            {
            case 2: // A
                if (count != 2)
                    *B = current + 2; // Must be in state AAB
                result = 1;
            case 0: // B
            case 4: // B
                *B = current + 1;
                if (count == 0) // AAB
                    result = 1;
                else            // BBB
                    result = -3;
            default:
                return -5; // Error
            }

            // Add on the result of calculating firstIndex's state
            indices[3] = current + 1;
            int count3 = QCOUNT(1, indices);
            switch (count3)
            {
            case 0: // AAB
                return result + 1;
            case 4: // BBB
                return result - 3;
            }
        case 4:
            switch (count)
            {
            case 4: // A
                break; // Must be in state AAB
            case 2: // B
                *B = current; // Could be in AAB or BBB
                break;
            default:
                return -5; // Error
            }

            switch (count2)
            {
            case 4: // A
                if (count != 2)
                    *B = current + 2;
                return 1;
            case 2: // B
                *B = current + 1;
                if (count == 0) // AAB
                    return 1;
                else            // BBB
                    return -3;
            default:
                return -5; // Error
            }
        }
    }
    else
    {
        int indices[4] = {*B, current, current + 1, current + 2};
        int count = QCOUNT(1, indices);
        switch (count)
        {
        case 0: // AAB
            return 1;
        case 4: // BBB
            return -3;
        default:
            return -5;
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

    if (*firstTriplet == -5)
    {
        *firstTriplet = count;
        if (count == 2)
            return 0;
    }

    switch (count)
    {
    case 0:
        return -1;
    case 2:
        return determine_hard_triplet(A, B, current, max, firstTriplet);
    case 4:
        A[1] = current;
        A[2] = current + 1;
        return 3;
    default:
        printf("Error: QCOUNT passed erroneous input: index = [ %d, %d, %d, %d]",
            indices[0], indices[1], indices[2], indices[3]);
        return -5;
    }
}

int mysub(int n)
{
    int A[3] = {1, -1, -1};
    int B = -1;

    int firstTriplet = -5;
    int count = predict_triplet(A, &B, 2, n, &firstTriplet);

    for (int i = 5; i <= n; i += 3)
    {
        // Early stop
        if (count > n - i)
            break;

        int result = predict_triplet(A, &B, i, n, &firstTriplet);
        if (result < -4)
            return -1;

        count += result;
    }

    if (count > 0)
        return A[0];
    else if (count < 0)
        return B;

    return 0;
}
