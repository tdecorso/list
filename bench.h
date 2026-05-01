#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <string.h>

#define ANSI_BOLD  "\x1b[1m"
#define ANSI_RED   "\x1b[31m"
#define ANSI_GREEN "\x1b[32m"
#define ANSI_CYAN  "\x1b[36m"
#define ANSI_RESET "\x1b[0m"

static inline long bench_now_ns(void) {
    struct timespec tp;
    clock_gettime(CLOCK_MONOTONIC, &tp);
    return tp.tv_sec * 1000000000L + tp.tv_nsec;
}

static inline int bench_cmp_long(const void* a, const void* b) {
    long la = *(const long*)a;
    long lb = *(const long*)b;
    return (la > lb) - (la < lb);
}

static inline double bench_percentile(long* sorted, int n, double p) {
    if (n == 0) return 0.0;
    double idx  = p * (n - 1);
    int    lo   = (int)idx;
    int    hi   = lo + 1;
    if (hi >= n) return (double)sorted[n - 1];
    double frac = idx - lo;
    return sorted[lo] + frac * (sorted[hi] - sorted[lo]);
}

#define BENCH(label, iters, batch, warmup, code)                               \
    do {                                                                       \
        for (int _w = 0; _w < (warmup); _w++) { code; }                        \
                                                                               \
        long* _samples = malloc((iters) * sizeof(long));                       \
        if (!_samples) { fprintf(stderr, "bench: malloc failed\n"); break; }   \
                                                                               \
        long _total = 0;                                                       \
                                                                               \
        for (int _i = 0; _i < (iters); _i++) {                                 \
            long _start = bench_now_ns();                                      \
            for (int _j = 0; _j < (batch); _j++) { code; }                     \
            long _elapsed = bench_now_ns() - _start;                           \
            _samples[_i] = _elapsed;                                           \
            _total       += _elapsed;                                          \
        }                                                                      \
                                                                               \
        qsort(_samples, (iters), sizeof(long), bench_cmp_long);                \
                                                                               \
        long   _ops = (long)(iters) * (batch);                                 \
        double _b   = 1 / (double)(batch);                                     \
        printf(ANSI_BOLD "\n\n=== %s ===\n\n" ANSI_RESET, (label));            \
        double p50  = bench_percentile(_samples, (iters), 0.500) * _b;         \
        double p90  = bench_percentile(_samples, (iters), 0.950) * _b;         \
        double p99  = bench_percentile(_samples, (iters), 0.990) * _b;         \
        printf("  p50 : %6.2f ns\n", p50);                                     \
        printf("  p90 : %6.2f ns\n", p90);                                     \
        printf("  p99 : %6.2f ns\n", p99);                                     \
        free(_samples);                                                        \
    } while (0)
