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

void bstDestroy(node *tree) {
  if (tree->left != NULL)
    bstDestroy(tree->left);
  if (tree->right != NULL)
    bstDestroy(tree->right);
  
  free(tree);
}