#define LIST_IMPLEMENTATION
#include "list.h"
#include "bench.h"

#define ITERS 1000000
#define WARMUP 100
#define BATCH 100

volatile int sink = 0;

int main(void) {
    BENCH("List allocation", ITERS, BATCH, WARMUP, {
        list_t* list = list_alloc(sizeof(int));
        sink += list->elem_size;
        list_free(list);
    });

    BENCH("List front insertion", ITERS, 1, WARMUP, {
        list_t* list = list_alloc(sizeof(int));
        for (int i = 0; i < 10000; ++i) {
            int* inserted = list_insert_front(list);
            *inserted = i;
            sink += *inserted;
        }
        list_free(list);
    });

    BENCH("List back insertion", ITERS, 1, WARMUP, {
        list_t* list = list_alloc(sizeof(int));
        for (int i = 0; i < 10000; ++i) {
            int* inserted = list_insert_back(list);
            *inserted = i;
            sink += *inserted;
        }
        list_free(list);
    });

    (void)sink;

    return 0;
}
