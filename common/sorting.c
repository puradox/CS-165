#include "sorting.h"
#include <assert.h>

#include "COMPARE.h"

#ifdef DEBUG
CompFunc compare = gt;
#else
CompFunc compare = compareGt;
#endif

void insertionSort(int arr[], int len)
{
  for (int i = 1; i < len; i++)
  {
    for (int j = i; j != 0 && compare(arr[j], arr[j - 1]); j--)
    {
      int temp = arr[j];
      arr[j] = arr[j - 1];
      arr[j - 1] = temp;
    }
  }
}
