#ifndef UTIL_H
#define UTIL_H

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include "COMPARE.h"

// rand returns a random index for an array of the specified size.
// This is used to get the random pivot for use in QuickSelect.
uint16_t randIndex(uint16_t size);

// swap modifies the given array by swapping two elements in place.
void swap(uint16_t arr[], uint16_t a, uint16_t b);

// max chooses the largest of the two specified numbers.
uint16_t max(uint16_t a, uint16_t b);

// min chooses the smallest of the two specified numbers.
uint16_t min(uint16_t a, uint16_t b);

// debug prints out the array specified
void debug(uint16_t arr[], uint16_t start, uint16_t end);

// shift modifies the given array to move the specified element to the left
// or right a number of times. This shifts the rest of the elements around.
void shift(uint16_t arr[], uint16_t pos, int shiftAmount);

// For finding # of comparisons
int getComps(void);
int allComps(void);
void resetComps(void);

#endif
