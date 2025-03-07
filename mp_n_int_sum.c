#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

#define N_THREADS 4

int sum = 0;
pthread_mutex_t mutex;

typedef struct {
    int start;
    int end;
} Range;

void* calculate_sum(void* arg) {
    Range* range = (Range*) arg;
    int local_sum = 0;

    for (int i = range->start; i <= range->end; i++) {
        local_sum += i;
    }

    pthread_mutex_lock(&mutex);
    sum += local_sum;
    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main() {
    int n;
    printf("Enter the number of integers to sum: ");
    scanf("%d", &n);

    pthread_t threads[N_THREADS];
    Range ranges[N_THREADS];

    pthread_mutex_init(&mutex, NULL);

    int segment_size = (int) ceil((double) n / N_THREADS);

    for (int i = 0; i < N_THREADS; i++) {
        ranges[i].start = i * segment_size + 1;
        ranges[i].end = (i + 1) * segment_size;

        if (ranges[i].end > n) {
            ranges[i].end = n;
        }

        pthread_create(&threads[i], NULL, calculate_sum, &ranges[i]);
    }

    for (int i = 0; i < N_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex);

    printf("The sum of the first %d integers is %d.\n", n, sum);

    return 0;
}
