#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define NUM_THREADS 4

int arr[1000]; // Global array
int size; // Global variable for size

// Insertion Sort function
void insertionSort(int start, int end) {
    for (int i = start + 1; i <= end; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= start && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

int main() {
    srand(time(NULL));
    int local_arr[] ={262,485,618,753,584,477,697,465,908,846,489,
                 324,659,324,552,604,775,498,393,758,424,44,12,866,891,675,
                 434,360,711,240,18,49,38,761,962,3,381,839,553,768,926,774,
                 545,46,541,231,670,660,218,536,945,134,804,552,747,964,922,614,
                 378,805,132,214,689,12};
                 
    size = sizeof(local_arr)/sizeof(local_arr[0]);
    for (int i = 0; i < size; i++) {
        arr[i] = local_arr[i];
    }

    clock_t start, end;
    start = clock();

    #pragma omp parallel num_threads(NUM_THREADS)
    {
        int thread_id = omp_get_thread_num();
        int start_index = thread_id * (size / NUM_THREADS);
        int end_index = (thread_id + 1) * (size / NUM_THREADS) - 1;
        insertionSort(start_index, end_index);
    }

    // Merging the sorted sections sequentially
    for (int i = 1; i < NUM_THREADS; i++) {
        int start_index = 0;
        int mid_index = (i * size) / NUM_THREADS - 1;
        int end_index = ((i + 1) * size) / NUM_THREADS - 1;
        if (end_index >= size) end_index = size - 1;
        insertionSort(start_index, end_index);
    }

    printf("Sorted array:\n");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    end = clock();
    double time_openmp = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Execution time (OpenMP): %f seconds\n", time_openmp);

    return 0;
}
