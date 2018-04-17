#include "sorting.h"
#include <assert.h>

#include "COMPARE.h"


// In-place insertion sort.
void insertionSort(int arr[], int len)
{
  #ifdef DEBUG
  CompFunc compare = gt;
  #else
  CompFunc compare = compareGt;
  #endif

  for (int i = 1; i < len; i++)
  {
    int j = i;
    while (j != 0 && compare(arr[j], arr[j - 1]))
    {
      int temp = arr[j];
      arr[j] = arr[j - 1];
      arr[j - 1] = temp;
      j--;
    }
  }
}