#include "COMPARE.h"

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
//	Comparisons to determine the biggest "k" array elements
//	COMPARE( 0,n ) initializes a random array of length n
//				all distinct values
//		returns  0 normally
//		returns -1 if n is out of range
//	COMPARE( x,y ) compares values of array[x] and array[y]
//		returns  1 if array[x] > array[y]
//		returns  2 if array[y] > array[x]
//		returns -1 if x or y is out of range
//	COMPARE( -1,k,Best[] ) checks whether Best[] contains
//			the indices of the biggest "k" in array
//		returns the number of comparisons performed
//			when the biggest "k" indices are okay
//		returns -1 if "k" is out of range
//		returns -1000 if any of the indices are wrong
//

int COMPARE(int arg1, int arg2, ...)
{
    va_list ap;
    static int number[COMPARELIMIT + 1];
    static int comp, size = 0;
    int *Best;
    int i, j, t;

    if (arg1 == 0)
    {
        if (arg2 < 10 || arg2 > COMPARELIMIT)
        {
            printf("******* ERROR: COMPARE(0,size) -- 'size' out of range ********** size=%d\n", arg2);
            return (-1);
        }
        for (i = 1; i <= arg2; i++)
            number[i] = i;
        for (i = arg2; i >= 1; i--)
        {
            j = i * dshrandom(0) + 1;
            if (j != i)
            {
                t = number[i];
                number[i] = number[j];
                number[j] = t;
            }
        }
        comp = 0;
        size = arg2;
        return (0);
    }
    if (arg1 == -1)
    {
        if (arg2 == -1)
            return comp;
        if (arg2 < 1 || arg2 > size || arg2 > KLIMIT)
        {
            printf("******* ERROR: COMPARE(-1,k,Best[]) -- 'k' out of range ********** k=%d\n", arg2);
            return (-1);
        }
        va_start(ap, arg2);
        Best = va_arg(ap, int *);
        va_end(ap);
        for (i = 0; i < arg2; i++)
        {
            if (Best[i] < 1 || Best[i] > size || number[Best[i]] != size - i)
            {
                if (Best[i] < 1 || Best[i] > size)
                    printf("******* GOT: number[Best[%d]] = number[%d] = out of range\n", i, Best[i]);
                else
                    printf("******* GOT: number[Best[%d]] = number[%d] = %d\n", i, Best[i], number[Best[i]]);

                int correctIndex = -1;
                int numberSize = sizeof(number) / sizeof(int);
                for (int j = 0; j < numberSize; j++)
                {
                    if (number[j] == size - i)
                    {
                        correctIndex = j;
                        break;
                    }
                }

                printf("******* EXPECTED: number[Best[%d]] = number[%d] = %d\n", i, correctIndex, size - i);

                printf("Best: ");
                for (int j = 0; j < arg2; j++)
                    printf("%2d ", j);
                printf("\n      ");
                for (int j = 0; j < arg2; j++)
                    printf("%2d ", Best[j]);
                printf("\n      ");
                for (int j = 0; j < arg2; j++)
                    printf("%2d ", number[Best[j]]);
                printf("\n");
                return (-1);
            }
        }
        return (comp);
    }
    if (arg1 < 1 || arg2 < 1 || arg1 > size || arg2 > size || arg1 == arg2)
        return (-1);
    comp++;
    if (number[arg1] > number[arg2])
        return (1);
    else
        return (2);
}

//
//	Random Number Generator
//		first called with seed
//		thereafter called with 0
//	Based on code appearing in
//	"Random number generators: good ones are hard to find"
//		by Stephen Park and Keith Miller
//		CACM 31 (Oct 1988) 1192-1201.
//
double dshrandom(long input)
{
    static long seed = 3125;
    static long a = 16807;
    static long m = 2147483647;
    static long q = 127773; /* m div a */
    static long r = 2836;   /* m mod a */
    long lo, hi, test;

    // Set seed
    if (input > 0)
    {
        seed = input;
        return 0;
    }

    // Reset seed to default
    if (input < 0)
    {
        seed = 3125;
        a = 16807;
        m = 2147483647;
        q = 127773; /* m div a */
        r = 2836;   /* m mod a */
        return 0;
    }

    hi = seed / q;
    lo = seed - (hi * q);
    test = a * lo - r * hi;
    if (test > 0)
        seed = test;
    else
        seed = test + m;
    /* seed equally in range 0...2^31 -1  */
    return (((double)seed) / (double)m);
}
