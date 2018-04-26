#ifndef PERF_H
#define PERF_H

int COUNT_TOTAL;
int COUNT_FIND;
int COUNT_TRIPLET;
int COUNT_TRIPLET_HARD;
int COUNT_PAIR;
int COUNT_SINGLETON;

void init_count();
void print_count();

int inc_find();
int inc_triplet();
int inc_triplet_hard();
int inc_pair();
int inc_singleton();

#endif
