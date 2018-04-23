#ifndef MYSUB_H
#define MYSUB_H

#include "triplet.h"
#include "find.h"

triplet predict_first(int A[], int *B); // 1-3 queries

triplet predict_singleton(int A[], int *B, int current); // 1 query
triplet predict_singleton_with_AA(int A[], int *B, int current); // 1 query
triplet predict_singleton_with_AB(int A[], int *B, int current); // 1 query

triplet predict_pair(int A[], int *B, int current);
triplet determine_hard_triplet(int A[], int *B, int current, triplet *first);
triplet determine_hard_triplet_without_B(int A[], int *B, int current, triplet *first);
triplet predict_triplet(int A[], int *B, int current, triplet *first);

int mysub(int n);

#endif
