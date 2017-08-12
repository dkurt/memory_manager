# Memory managers
Experiments with different memory management models that solve problem with
memory distribution between users in time.

## Problem

Every user requires some piece of memory in known period of deterministic
time. After it, this memory might be reused by other users. Memory management
model produces pointers to beginnings of memory blocks for every user in some
continuous pre-allocated memory space.

## Example

| User ID | Memory usage (bytes) | Interval (iterations) |
|--------:|---------------------:|----------------------:|
|       0 |                    2 |                [3, 5] |
|       1 |                    1 |                [1, 4] |
|       2 |                    3 |                [5, 8] |

It's easier to represent cases as tables where users by rows, iterations by
columns and values are number of bytes:

```
 iter | 1 2 3 4 5 6 7 8
------+----------------
User1 | 0 0 2 2 2 0 0 0
User2 | 1 1 1 1 0 0 0 0
User3 | 0 0 0 0 3 3 3 3
```

## Quality metrics and models comparison
Memory management model is correct if:

* Maximal memory usage is less or equal than sum of all memory sizes required by
users. Otherwise we can just allocate memory separately.
* On every iteration memory blocks are used by users don't intersect.

|                 Model code name |     Ratio |
|--------------------------------:|----------:|
|                 Reuse or create |      0.67 |
