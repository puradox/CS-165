#ifndef BST_H
#define BST_H

#include "COMPARE.h"
#include "util.h"

//#define DEBUG

struct node
{
    int value;
    struct node *left;
    struct node *right;
};

typedef struct node node;

// bstConstruct constructs a binary search tree from the given array.
node *bstConstruct(int arr[], int start, int end);

// bstInsert takes the binary search tree and inserts an element in order.
void bstInsert(node *tree, int value);

// bstToArray converts the binary search tree to an ascending ordered array.
int *bstToArray(node *tree);

void bstDestroy(node *tree);

#endif
