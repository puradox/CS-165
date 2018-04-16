#ifndef UTIL_H
#define UTIL_H

#include <assert.h>
#include <stdlib.h>
#include "COMPARE.h"

// rand returns a random index for an array of the specified size.
// This is used to get the random pivot for use in QuickSelect.
int randIndex(int size);

// swap modifies the given array by swapping two elements in place.
void swap(int arr[], int a, int b);

// max chooses the largest of the two specified numbers.
int max(int a, int b);

// min chooses the smallest of the two specified numbers.
int min(int a, int b);

// debug prints out the array specified
void debug(int arr[], int start, int end);

// shift modifies the given array to move the specified element to the left
// or right a number of times. This shifts the rest of the elements around.
void shift(int arr[], int pos, int shiftAmount);

// For finding # of comparisons
int getComps(void);
int allComps(void);
void resetComps(void);

#endif
