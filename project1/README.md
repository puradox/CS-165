# Project 1 - Find k largest

Write a routine in C that, using as few element comparisons as possible,
finds the indices of array elements that have the k largest values, in
descending value order, from an array of n elements.

[Grading Rubric](http://www.ics.uci.edu/~dan/class/165/PROJECTS/SELECT/Rubric1.html)

## Statistics

| Algorithm  | Size of n | Size of k | Worse Case Comparisons |
| ---------- | --------- | --------- | ---------------------- |
| pqueue     | 100       | 10        | 325                    |
| pqueue     | 10000     | 40        | 16054                  |
| select     | 100       | 10        | 897                    |
| select     | 10000     | 40        | 91597                  |
| heap       | 100       | 10        | 305                    |
| heap       | 10000     | 40        | 19975                  |
| minheap    | 100       | 10        | 292                    |
| minheap    | 10000     | 40        | 12467                  |
| bst        | 100       | 10        | 246                    |
| bst        | 10000     | 40        | 11698                  |
| tournament | 100       | 10        | 177                    |
| tournament | 10000     | 40        | 10573                  |
