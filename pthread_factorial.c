#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N_THREADS 3

long long thread_results[N_THREADS];

struct Range {
    int start;
    int end;
    int thread_id; // Add thread_id for proper indexing
};

void* calculate_factorial(void* arg) {
    struct Range* range = (struct Range*)arg;
    long long local_result = 1;

    for (int i = range->start; i <= range->end; i++) {
        local_result *= i;
    }

    thread_results[range->thread_id] = local_result; // Store result in the correct thread index
    return NULL;
}

int main() {
    int n;
    printf("Enter a number to calculate its factorial: ");
    scanf("%d", &n);

    if (n < 0) {
        printf("Factorial is not defined for negative numbers.\n");
        return 1;
    } else if (n == 0 || n == 1) {
        printf("The factorial of %d is 1.\n", n);
        return 0;
    }

    pthread_t threads[N_THREADS];
    struct Range ranges[N_THREADS];
    int segment_size = n / N_THREADS;

    for (int i = 0; i < N_THREADS; i++) {
        ranges[i].start = i * segment_size + 1;
        ranges[i].end = (i == N_THREADS - 1) ? n : (i + 1) * segment_size;
        ranges[i].thread_id = i;

        pthread_create(&threads[i], NULL, calculate_factorial, &ranges[i]);
    }

    for (int i = 0; i < N_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    long long factorial = 1;
    for (int i = 0; i < N_THREADS; i++) {
        factorial *= thread_results[i];
    }

    printf("The factorial of %d is %lld.\n", n, factorial);

    return 0;
}
