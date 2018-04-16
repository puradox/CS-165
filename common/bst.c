#include "bst.h"
#include <assert.h>

node *bstConstruct(int arr[], int start, int end)
{
  assert(arr != NULL);
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
    rootNode->left  = bstConstruct(arr, start, currentPos - 1);
    rootNode->right = bstConstruct(arr, currentPos + 1, end);

    return rootNode;
  }
}

void bstInsertNode(node *tree, node *valueNode)
{
#ifdef DEBUG
    CompFunc compare = lt;
#else
    CompFunc compare = compareLt;
#endif

    if (compare(valueNode->value, tree->value))
    {
        if (tree->right != NULL)
            bstInsertNode(tree->right, valueNode);
        else
            tree->right = valueNode;
    }
    else
    {
        if (tree->left != NULL)
            bstInsertNode(tree->left, valueNode);
        else
            tree->left = valueNode;
    }
}

void bstInsert(node *tree, int value)
{
    node *valueNode = malloc(sizeof(node));
    valueNode->value = value;
    valueNode->left = NULL;
    valueNode->right = NULL;

    bstInsertNode(tree, valueNode);
}

void toArray(node *tree, int *arr, int *currentSize, int end)
{
    if (tree->left != NULL)
        toArray(tree->left, arr, currentSize, end);

    int index = *currentSize;
    arr[index] = tree->value;
    (*currentSize)++;

    if (tree->right != NULL)
        toArray(tree->right, arr, currentSize, end);
}

int *bstToArray(node *tree, int size)
{
    int *arr = malloc(sizeof(int) * size);
    int *currentSize = malloc(sizeof(int));
    *currentSize = 0;
    toArray(tree, arr, currentSize, size - 1);
    free(currentSize);
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
