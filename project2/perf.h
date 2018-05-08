#ifndef PERF_H
#define PERF_H

int COUNT_TOTAL;
int COUNT_MYSUB;
int COUNT_EARLY_STOP;
int COUNT_FIND;
int COUNT_TRIPLET;
int COUNT_TRIPLET_HARD;
int COUNT_PAIR;
int COUNT_SINGLETON;

void init_count();
void print_count();

int inc_find();
int inc_early_stop();
int inc_mysub();
int inc_triplet();
int inc_triplet_hard();
int inc_pair();
int inc_singleton();

#endif
