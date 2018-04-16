#include "sorting.h"
#include <assert.h>

#include "COMPARE.h"

#ifdef DEBUG
CompFunc compare = lt;
#else
CompFunc compare = compareLt;
#endif


// In-place insertion sort.
void insertionSort(int arr[], int len)
{
  for (int i = 1; i < len; i++)
  {
    int j = i;
    while (compare(arr[j], arr[j - 1]) && j != 0)
    {
      int temp = arr[j];
      arr[j] = arr[j - 1];
      arr[j - 1] = temp;
      j--;
    }
  }
}