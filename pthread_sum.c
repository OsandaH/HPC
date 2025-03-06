#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N_THREADS 10
#define ARRAY_SIZE 100

int array[ARRAY_SIZE] = {
    23, 45, 67, 12, 89, 34, 56, 78, 90, 11, 45, 67, 89, 12, 34, 56, 78, 90, 11,
    23, 67, 89, 12, 34, 56, 78, 90, 11, 23, 45, 89, 12, 34, 56, 78, 90, 11, 23,
    45, 67, 12, 34, 56, 78, 90, 11, 23, 45, 67, 89, 34, 56, 78, 90, 11, 23, 45,
    67, 89, 12, 56, 78, 90, 11, 23, 45, 67, 89, 12, 34, 78, 90, 11, 23, 45, 67,
    89, 12, 34, 56, 90, 11, 23, 45, 67, 89, 12, 34, 56, 78, 11, 23, 45, 67, 89,
    12, 34, 56, 78, 90
};

int thread_sums[N_THREADS] = {0}; 

struct Range {
    int start;
    int end;
};

void* calculate_sum(void* arg) {
    struct Range* range = (struct Range*)arg;
    int local_sum = 0;

    for (int i = range->start; i <= range->end; i++) {
        local_sum += array[i];
    }

    thread_sums[range->start / (ARRAY_SIZE / N_THREADS)] = local_sum;
    return NULL;
}

int main() {
    pthread_t threads[N_THREADS];
    struct Range ranges[N_THREADS];
    int segment_size = ARRAY_SIZE / N_THREADS;

    for (int i = 0; i < N_THREADS; i++) {
        ranges[i].start = i * segment_size;
        ranges[i].end = (i == N_THREADS - 1) ? ARRAY_SIZE - 1 : (i + 1) * segment_size - 1;

        pthread_create(&threads[i], NULL, calculate_sum, &ranges[i]);
    }

    for (int i = 0; i < N_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    int total_sum = 0;
    for (int i = 0; i < N_THREADS; i++) {
        total_sum += thread_sums[i];
    }

    printf("The sum of the array elements is %d.\n", total_sum);

    return 0;
}
