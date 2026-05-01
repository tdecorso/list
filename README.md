# Doubly-linked list (C Implementation)

This implementation allocates (and deallocates) memory for each node. I consider it as a baseline for further experiments with linked lists optimization.

## Usage
Just include the **list.h** header in your project.

### List Allocation and Deallocation
```
list_t* a_list = list_alloc(sizeof(int));
list_free(a_list);
```

### List node insertion
```
list_t* a_list = list_alloc(sizeof(int));
int* first = list_insert_front(a_list); // you can also use insert_back or insert_at
*first = 1;
list_free(a_list);
```

### List node deletion
```
list_t* a_list = list_alloc(sizeof(int));
int* first = list_insert_front(a_list); // you can also use insert_back or insert_at
*first = 1;
int removed = 0;
list_delete_at(a_list, 0, &removed); // you can also use delete_back or delete_front
list_free(a_list);
```

## Testing

Run tests:

```
gcc test.c -o test && ./test
```

## Benchmark

Benchmark utilities are included (bench.h and bench.c)

Run benchmark:
```
gcc bench.c -o bench && ./bench
```

### Results

Measured over 1e6 iterations with 100 warmup cycles:

| Operation                 |    p50    |     p90     |    p99    |
| -----------------------   | --------- | ----------  | --------- | 
| Alloc + Free              | 008.19 ns | 008.83 ns   | 009.37 ns |
| Front insert   (10000)    | 348.60 µs | 453.66 µs   | 723.73 µs |
| Back insert    (10000)    | 362.04 µs | 433.11 µs   | 598.51 µs |
| List traversal (10000)    | 419.53 µs | 551.27 µs   | 723.48 µs |

For comparison, my benchmarks show that inserting one element in this list is approximately **22** times slower than in my dynamic array.




