#include <stdio.h>
#include <stdlib.h>

// This node structure allows us to create a linked list, which is important to
// support O(k) insertions in the worst case.
struct node
{
  uint index;
  struct node *next;
};

typedef struct node *LinkedList;

// Inserts a new index into the linked list in sorted order.
// Returns 1 if there were no errors, 0 otherwise.
int insert(int i, LinkedList list)
{
  // Compare against the first list element
  int compRes = COMPARE(list->index, i);

  // Create the new node to be inserted
  LinkedList newNode = (LinkedList)malloc(sizeof(struct node));
  newNode->index = i;

  if (compRes == 1)  // Next element is smaller than all elements in list.
  {
    // Create new head node
    newNode->next = list;

    // Update head node
    list = newNode;
    return 1;
  }
  else if (compRes == 2)  // Next element is greater than first element in list.
  {
    LinkedList prev = list;
    LinkedList temp = list->next;

    while (temp != NULL)
    {
      compRes = COMPARE(temp->index, i);
      if (compRes == 1)
      {
        // Add newNode in between prev and temp
        newNode->next = temp;
        prev->next = newNode;
        return 1;
      }
      else if (compRes == 2)
      {
        // Keep looking
        prev = temp;
        temp = temp->next;
      }
      else
      {
        // ERROR: out of range value received
        printf("Error in insert with indicies %d, %d: Out of range.\n", temp->index, i);
        return 0;
      }
    }

    // We reached the end of the list, so insert after the last element.
    newNode->next = NULL;
    prev->next = newNode;
    return 1;
  }
  else
  {
    // ERROR: out of range value received
    printf("Error in insert with indicies %d, %d: Out of range.\n", list->index, i);
    return 0;
  }
}

// Removes the smallest element in the sorted linked list.
// Returns 1 if there were no errors, 0 otherwise.
int removeSmallest(LinkedList list)
{
  LinkedList temp = list;
  list = list->next;

  free(temp);
}

// Implements k greatest by inserting the first k elements into a linked list in
// sorted order, then finding where each new element will land in the linked
// list. We then discard the leftmost (smallest) node.
// Returns 1 if there were no errors, 0 otherwise.
//
// Bounds:
//   10 <= n <= 10000
//   1  <= k <= 100
int doalg(int n, int k, int Best[])
{
  printf("n=%d, k=%d\n", n, k);
  // Since array data is obfuscated from this algorithm, we represent all
  // values using their indicies.

  // Create the linked list and add the first element.
  LinkedList list = (LinkedList)malloc(sizeof(struct node));
  list->index = 1;
  list->next = NULL;

  // Add the next k - 1 elements to the linked list in sorted order.
  for (unsigned short i = 2; i <= k; ++i)
  {
    if (insert(i, list) == 0)  // Catch possible error
      return 0;
  }

  // Add each of the remaining n - k elements to the list, discarding one
  // linked list node after each insertion.
  for (unsigned short i = k + 1; i <= n; ++i)
  {
    if (insert(i, list) == 0)  // Catch possible error
      return 0;
    removeSmallest(list);
  }

  return 1; // Return with no errors.
}
