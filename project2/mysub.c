// mysub.h

// Main function. Takes number of elements as input and outputs an index of the
// majority class.
int mysub(int n);

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

// Calculate the result knowing it depends on the final three indices.
// Takes 1-2 queries
int calculate_final_three(int A[], int *B, int count, int n);

// Calculate the result knowing it depends on the final three indices.
// Takes 1 query
int calculate_final_two(int A[], int *B, int count, int n);

// Calculate the result knowing it depends on the final three indices.
// Takes 1 query
int calculate_final_one(int A[], int *B, int n);

// Find instances of A and B for further calculations.
void search_for_AB(int A[], int *B, int zero, int twos[], int numTwos);

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
    int remaining = n;

    // We need to keep track of all of the fours and twos. Here we decide to use
    // the starting index of each quad for tracking.
    int *fours = malloc(numQuads * sizeof(int));
    int *twos  = malloc(numQuads * sizeof(int));
    int numFours = 0;
    int numTwos  = 0;

    // Let's also keep track of one zero for edge cases.
    int zero = -1;

    // First, let's classify each quad.
    for (int i = 1; i < n - 2; i += 4)
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
            return -1;
        }
    }

    // Now that each quad is classified, we need to keep track of two extra
    // values: the total count calculated as numOfA - numOfB, and the maximum
    // swing in count possible with our uncalculated quads.
    int count = 0;
    int maxSwing = 4*numFours + 2*numTwos;

    // We start with fours since they require the lowest number of comparisons.
    if (numFours == 1)
    {
        count += consider_single_four(A, B, fours[0]);
        remaining -= 4;
        maxSwing -= 4;

        // Check if we should stop early.
        int absCount = count > 0 ? count : -count;
        if (absCount > remaining || maxSwing < absCount)
        {
            if (*B == -1)
                search_for_AB(A, B, zero, twos, numTwos);
            return calculate_result(A, B, count);
        }
    }
    else if (numFours > 1)
    {
        int excess = numFours % 2; // Check if there's an odd man out
        
        // Calculate pairs
        for (int i = 0; i+1 < numFours; i += 2)
        {
            count += consider_fours(A, B, fours[i], fours[i+1]);
            remaining -= 8;
            maxSwing -= 8;

            // Check if we should stop early.
            int absCount = count > 0 ? count : -count;
            if (absCount > remaining || maxSwing < absCount)
            {
                if (*B == -1)
                    search_for_AB(A, B, zero, twos, numTwos);
                return calculate_result(A, B, count);
            }
        }

        // Check for odd man out and calculate if necessary
        if (excess == 1)
        {
            count += consider_single_four(A, B, fours[numFours - 1]);
            remaining -= 4;
            maxSwing -= 4;

            // Check if we should stop early.
            int absCount = count > 0 ? count : -count;
            if (absCount > remaining || maxSwing < absCount)
            {
                if (*B == -1)
                    search_for_AB(A, B, zero, twos, numTwos);
                return calculate_result(A, B, count);
            }
        }
    }

    if (twos[0] == 1 && *B == -1)
        search_for_AB(A, B, zero, twos, numTwos);

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
            if (*B == -1)
                search_for_AB(A, B, zero, twos, numTwos);
            return calculate_result(A, B, count);
        }
    }

    // Finally, we calculate the last few values.
    search_for_AB(A, B, zero, twos, numTwos);
    switch (remaining)
    {
    case 3:
        return calculate_final_three(A, B, count, n);
    case 2:
        return calculate_final_two(A, B, count, n);
    case 1:
        return calculate_final_one(A, B, n);
    case 0:
        return 0;
    default:
        printf("Error: remainder not in bounds 4 > x => 0.\n");
    }

    // We should never get here.
    return -1;
}

int consider_fours(int A[], int *B, int firstSet, int secondSet)
{
    // Fill in A and B if possible
    if (A[1] == -1)
    {
        A[0] = firstSet;
        A[1] = firstSet + 1;
        A[2] = firstSet + 2;
        
        int indices[4] = {A[0], A[1], A[2], secondSet};
        if (QCOUNT(1, indices) == 4)
            return 8;
        else
        {
            *B = secondSet;
            return 0;
        }
    }
    else
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
            if (*B == -1)
                *B = firstSet;
            return -8;
        default:
            printf("Error: QCOUNT called with incorrect indices.\n");
            return -1;
        }
    }
}

int consider_single_four(int A[], int *B, int set)
{
    // Fill in A if possible
    if (A[1] == -1)
    {
        A[0] = set;
        A[1] = set + 1;
        A[2] = set + 2;

        return 4;
    }
    else
    {
        int indices[4] = {A[0], A[1], A[2], set};
        if (QCOUNT(1, indices) == 4)
            return 4;
        else
        {
            if (*B == -1)
                *B = set;
            return -4;
        }
    }
}

int consider_single_two(int A[], int *B, int set)
{
    if (set == 1)
    {
        int indices[4] = {*B, set, set+1, set+2};
        int result = QCOUNT(1, indices);
        switch (result)
        {
        case 4:
            return -2; // BBBA
        case 2:
            indices[1] = set + 3;
            if (QCOUNT(1, indices) == 0)
                return 2; // AAAB
            else
                return -2;  // BBBA
        case 0:
            return 2; // AAAB
        default:
            printf("Error: QCOUNT called with incorrect indices.\n");
            return -1;
        }
    }
    else
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
            return -1;
        }
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

int calculate_final_three(int A[], int *B, int count, int n)
{
    int indices[4] = {A[0], n-2, n-1, n};
    int result = QCOUNT(1, indices);
    switch (result)
    {
    case 4:
        return A[0];
    case 2:
        indices[1] = A[1];
        if (QCOUNT(1, indices) == 0)
            return *B;
        else
            return A[0];
    case 0:
        return *B;
    default:
        printf("Error: QCOUNT called with incorrect indices.\n");
        return -1;
    }
}

int calculate_final_two(int A[], int *B, int count, int n)
{
    int indices[4] = {A[0], A[1], n-1, n};
    int result = QCOUNT(1, indices);
    switch (result)
    {
    case 4:
        return A[0];
    case 2:
        return 0;
    case 0:
        return *B;
    default:
        printf("Error: QCOUNT called with incorrect indices.\n");
        return -1;
    }
}

int calculate_final_one(int A[], int *B, int n)
{
    int indices[4] = {A[0], A[1], A[2], n};
    if (QCOUNT(1, indices) == 4)
        return A[0];
    else
        return *B;
}

void search_for_AB(int A[], int *B, int zero, int twos[], int numTwos)
{
    int two = twos[numTwos - 1];
    if (A[1] == -1 || *B == -1)
    {
        if (zero == -1)
        {
            int indices[4] = {A[0], two + 1, two + 2, two + 3};
            int result = QCOUNT(1, indices);
            switch (result)
            {
            case 4:
                if (A[1] == -1)
                    A[1] = two + 2;
                if (A[2] == -1)
                    A[2] = two + 3;
                if (*B == -1)
                    *B = two;
                break;
            case 2:
                indices[0] = two;
                indices[1] = A[0];
                result = QCOUNT(1, indices);
                switch (result)
                {
                case 4:
                    if (A[1] == -1)
                        A[1] = two + 2;
                    if (A[2] == -1)
                        A[2] = two + 3;
                    if (*B == -1)
                        *B = two + 1;
                    break;
                case 2:
                    indices[1] = two + 1;
                    indices[2] = A[0];
                    if (QCOUNT(1, indices) == 2)
                    {
                        if (A[1] == -1)
                            A[1] = two;
                        if (A[2] == -1)
                            A[2] = two + 1;
                        if (*B == -1)
                            *B = two + 3;
                    }
                    else
                    {
                        if (A[1] == -1)
                            A[1] = two;
                        if (A[2] == -1)
                            A[2] = two + 1;
                        if (*B == -1)
                            *B = two + 2;
                    }
                    break;
                case 0:
                    if (A[1] == -1)
                        A[1] = two;
                    if (*B == -1)
                        *B = two + 1;
                    break;
                default:
                    printf("Error: QCOUNT called with incorrect indices.\n");
                }
                break;
            case 0:
                indices[0] = two;
                indices[1] = A[0];
                if (QCOUNT(1, indices) == 2)
                {
                    if (A[1] == -1)
                        A[1] = two + 1;
                    if (*B == -1)
                        *B = two;
                }
                else
                {
                    indices[1] = two + 1;
                    indices[2] = A[0];
                    if (QCOUNT(1, indices) == 2)
                    {
                        if (A[1] == -1)
                            A[1] = two + 2;
                        if (*B == -1)
                            *B = two;
                    }
                    else
                    {
                        if (A[1] == -1)
                            A[1] = two + 3;
                        if (*B == -1)
                            *B = two;
                    }
                }
                break;
            default:
                printf("Error: QCOUNT called with incorrect indices.\n");
            }
        }
        else
        {
            int indices[4] = {A[0], zero + 1, zero + 2, zero + 3};
            if (QCOUNT(1, indices) == 0)
            {
                if (A[1] == -1)
                    A[1] = zero;
                indices[0] = zero;
                indices[1] = A[0];
                if (QCOUNT(1, indices) == 0)
                {
                    if (A[2] == -1)
                        A[2] = zero + 1;
                    if (*B == -1)
                        *B = zero + 2;
                }
                else
                {
                    if (*B == -1)
                        *B = zero + 1;
                    indices[1] = zero + 1;
                    indices[2] = A[0];
                    
                    if (A[2] == -1)
                    {
                        if (QCOUNT(1, indices) == 0)
                            A[2] = zero + 2;
                        else
                            A[2] = zero + 3;
                    }
                }
            }
            else
            {
                if (*B == -1)
                    *B = zero;
                indices[0] = zero;
                indices[1] = A[0];
                if (QCOUNT(1, indices) == 0)
                {
                    if (A[1] == -1)
                        A[1] = zero + 1;
                    indices[1] = zero + 1;
                    indices[2] = A[0];

                    if (A[2] == -1)
                    {
                        if (QCOUNT(1, indices) == 0)
                            A[2] = zero + 2;
                        else
                            A[2] = zero + 3;
                    }
                }
                else
                {
                    if (A[1] == -1)
                        A[1] = zero + 2;
                    if (A[2] == -1)
                        A[2] = zero + 3;
                }
            }
        }
    }

    if (A[2] == -1 && numTwos > 1)
        search_for_AB(A, B, zero, twos, numTwos - 1);
}

// END mysub.c
