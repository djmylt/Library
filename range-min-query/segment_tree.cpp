/**
 * Segment Tree
 * A heap-like data structure which answers range minimum queries in O(logn)
 * Build time is O(n)
 * Author: Shrey Banga
 */
#include <cstdio>
#include <cstdlib>
#include <time.h>
#include "segment_tree.hpp"

int main(int argc, char **argv) {
    int count = atoi(argv[1]);
    clock_t start;
    double time = 0;
    FILE *list_file = fopen("list", "r");
    int *a = new int[count];
    int x;
    int i, j;
    for(i = 0; i < count; i++)
        fscanf(list_file, "%d", &a[i]);
    fclose(list_file);

    SegmentTree<int> t(a, count);

    FILE *result_file = fopen("segment_tree_results", "w");

    FILE *query_file = fopen("queries", "r");

    while(fscanf(query_file, "%d %d\n", &i, &j) == 2) {
        start = clock();
        x = t.rmq(i,j);
        time += (double)(clock() - start) / (CLOCKS_PER_SEC/1000);
        fprintf(result_file, "%d\n", x);
    }

    fclose(query_file);

    fclose(result_file);
    FILE *process_file = fopen("/proc/self/statm", "r");
    unsigned long size, resident, share, text, lib, data, dt;
#ifndef PROFILE
    printf("Segment Tree results:\n");
    printf("Average time taken: %f\n", time/count);
    printf("Total time taken: %f\n", time);
    if (fscanf(process_file, "%lu %lu %lu %lu %lu %lu %lu", &size, &resident, &share, &text, &lib, &data, &dt) == 7) {
        printf("Total Size:     %lu\n", size);
        printf("Resident Size:  %lu\n", resident);
        printf("Shared Memory:  %lu\n", share);
        printf("Code Size:      %lu\n", text);
        printf("Library Memory: %lu\n", lib);
        printf("Data Size:      %lu\n", data);
        printf("Dirty Pages:    %lu\n", dt);
    }
#else
    if (fscanf(process_file, "%lu %lu %lu %lu %lu %lu %lu", &size, &resident, &share, &text, &lib, &data, &dt) == 7) {
        printf("%f,%lu,%lu\n", time, size, data);
    }
#endif
    fclose(process_file);
}

