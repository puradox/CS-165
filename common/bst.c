#include "bst.h"
#include <assert.h>

node *bstConstruct(int arr[], int start, int end)
{
  assert(start <= end);

  if (start == end)
  {
    node *result = malloc(sizeof(node));

    result->value = arr[start];
    result->left  = NULL;
    result->right = NULL;

    return result;
  }
  else if (start + 1 == end)
  {
    node *result = malloc(sizeof(node));

    result->value = arr[end];
    result->left  = malloc(sizeof(node));
    result->right = NULL;

    result->left->value = arr[start];
    result->left->left  = NULL;
    result->left->right = NULL;

    return result;
  }
  else
  {
    int currentPos = ((end - start) / 2) + start;
    int root = arr[currentPos];
    node *rootNode = malloc(sizeof(node));

    rootNode->value = root;
    rootNode->left  = bstConstruct(arr, start, currentPos);
    rootNode->right = bstConstruct(arr, currentPos, end);

    return rootNode;
  }
}

void bstInsertNode(node *tree, node *node)
{
#ifdef DEBUG
    CompFunc compare = lt;
#else
    CompFunc compare = compareLt;
#endif

    if (compare(node->value, tree->value))
    {
        if (tree->right != NULL)
            bstInsertNode(tree->right, node);
        else
            tree->right = node;
    }
    else
    {
        if (tree->left != NULL)
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
    assert(cursor != NULL);
    assert(arr != NULL);
    assert(currentSize != NULL);
    assert(*currentSize <= end);

    if (cursor->left != NULL)
        return toArray(cursor->left, arr, currentSize, end);
    arr[*currentSize] = cursor->value;
    (*currentSize)++;
    if (cursor->right != NULL)
        toArray(cursor->right, arr, currentSize, end);
}

int *bstToArray(node *tree, int size)
{
    int *arr = malloc(sizeof(int) * size);
    int currentSize = 0;
    toArray(tree, arr, &currentSize, size - 1);
    return arr;
}

int bstMin(node *tree)
{
    assert(tree != NULL);
    if (tree->left != NULL)
        return bstMin(tree->left);
    return tree->value;
}

void bstDestroy(node *tree) {
  if (tree->left != NULL)
    bstDestroy(tree->left);
  if (tree->right != NULL)
    bstDestroy(tree->right);

  free(tree);
}
