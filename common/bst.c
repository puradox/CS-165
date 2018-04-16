#include "bst.h"
#include <assert.h>

void bstInsertNode(node *tree, node *node)
{
#ifdef DEBUG
    CompFunc compare = lt;
#else
    CompFunc compare = compareLt;
#endif

    if (compare(node->value, tree->value))
    {
        if (tree->right)
            bstInsertNode(tree->right, node);
        else
            tree->right = node;
    }
    else
    {
        if (tree->left)
            bstInsertNode(tree->left, node);
        else
            tree->left = node;
    }
}

void bstInsert(node *tree, int value)
{
    node *node = malloc(sizeof(node));
    node->value = value;
    bstInsertNode(tree, node);
}

void toArray(node *cursor, int *arr, int *currentSize, int end)
{
    assert(*currentSize <= end);
    if (cursor->left)
        return toArray(cursor->left, arr, currentSize, end);
    arr[*currentSize++] = cursor->value;
    toArray(cursor->right, arr, currentSize, end);
}

int *bstToArray(node *tree, int size)
{
    int *arr = malloc(sizeof(int) * size);
    int *currentSize = 0;
    toArray(tree, arr, currentSize, size - 1);
    return arr;
}

int bstMin(node *tree)
{
    assert(tree);
    if (tree->left)
        return bstMin(cursor->left);
    return cursor->value;
}
