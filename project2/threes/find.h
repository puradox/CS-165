#ifndef FIND_H
#define FIND_H

#include "triplet.h"

void set_A(int A[], int element);

// Find another instance of A or B.
int find(int A[], int *B); // 1-2 queries

int find_from_AAB(int A[], int *B, int current);          // 1-2 queries
int find_from_AAB_with_AA(int A[], int *B, int current);  // 1-2 queries
int find_from_AAB_with_AB(int A[], int *B, int current);  // 1-2 queries
int find_from_AAB_with_AAA(int A[], int *B, int current); // 1-2 queries
int find_from_AAB_with_AAB(int A[], int *B, int current); // 1 query

int find_from_ABB(int A[], int *B, int current);          // 1-2 queries
int find_from_ABB_with_AA(int A[], int *B, int current);  // 1-2 queries
int find_from_ABB_with_AB(int A[], int *B, int current);  // 1-2 queries
int find_from_ABB_with_AAA(int A[], int *B, int current); // 1 query
int find_from_ABB_with_AAB(int A[], int *B, int current); // 1-2 queries

// EDGE CASE
// Find B when first is hard and all other triplets are ABB.
// Takes 1-3 queries, 7/3 = 2.33 average.
int find_from_two_ABBs(int A[], int *B, int left, int right);

#endif
