#ifndef COMPARE_H
#define COMPARE_H

#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>

#define COMPARELIMIT 10000
#define KLIMIT 100

//#define DEBUG

typedef int8_t (*CompFunc)(uint16_t, uint16_t);

// Comparators
int8_t lt(uint16_t a, uint16_t b);
int8_t gt(uint16_t a, uint16_t b);
int8_t compareLt(uint16_t a, uint16_t b); // uses COMPARE
int8_t compareGt(uint16_t a, uint16_t b); // uses COMPARE

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
int COMPARE(int arg1, int arg2, ...);

//
//	Random Number Generator
//		first called with seed
//		thereafter called with 0
//	Based on code appearing in
//	"Random number generators: good ones are hard to find"
//		by Stephen Park and Keith Miller
//		CACM 31 (Oct 1988) 1192-1201.
//
double dshrandom(long input);

#endif
