#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define NUM_THREADS 4
#define ARRAY_SIZE 64

int arr[ARRAY_SIZE];  // Shared array
int sorted_arr[ARRAY_SIZE];  // Sorted array for merging

// Structure to pass arguments to threads
typedef struct {
    int start;
    int end;
} ThreadData;

// Function to perform insertion sort on a subarray
void insertionSort(int arr[], int start, int end) {
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

// Thread function for sorting a portion of the array
void *thread_sort(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    insertionSort(arr, data->start, data->end);
    pthread_exit(NULL);
}

// Function to merge sorted parts
void merge(int arr[], int start1, int end1, int start2, int end2) {
    int i = start1, j = start2, k = start1;
    
    while (i <= end1 && j <= end2) {
        if (arr[i] < arr[j])
            sorted_arr[k++] = arr[i++];
        else
            sorted_arr[k++] = arr[j++];
    }
    
    while (i <= end1) sorted_arr[k++] = arr[i++];
    while (j <= end2) sorted_arr[k++] = arr[j++];
    
    for (int i = start1; i <= end2; i++)
        arr[i] = sorted_arr[i]; // Copy back to original array
}

// Function to merge all sorted parts
void mergeAll() {
    int mid1 = ARRAY_SIZE / 4 - 1;
    int mid2 = ARRAY_SIZE / 2 - 1;
    int mid3 = 3 * ARRAY_SIZE / 4 - 1;

    merge(arr, 0, mid1, mid1 + 1, mid2);
    merge(arr, mid2 + 1, mid3, mid3 + 1, ARRAY_SIZE - 1);
    merge(arr, 0, mid2, mid2 + 1, ARRAY_SIZE - 1);
}

int main() {
    int temp_arr[] = {262,485,618,753,584,477,697,465,908,846,489,
        324,659,324,552,604,775,498,393,758,424,44,12,866,891,675,
        434,360,711,240,18,49,38,761,962,3,381,839,553,768,926,774,
        545,46,541,231,670,660,218,536,945,134,804,552,747,964,922,614,
        378,805,132,214,689,12};
    
    for (int i = 0; i < ARRAY_SIZE; i++)
        arr[i] = temp_arr[i];

    pthread_t threads[NUM_THREADS];
    ThreadData thread_data[NUM_THREADS];

    int part_size = ARRAY_SIZE / NUM_THREADS;

    clock_t start = clock();

    // Create threads to sort individual parts
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_data[i].start = i * part_size;
        thread_data[i].end = (i == NUM_THREADS - 1) ? (ARRAY_SIZE - 1) : (thread_data[i].start + part_size - 1);
        pthread_create(&threads[i], NULL, thread_sort, &thread_data[i]);
    }

    // Join threads
    for (int i = 0; i < NUM_THREADS; i++)
        pthread_join(threads[i], NULL);

    // Merge sorted parts
    mergeAll();

    clock_t end = clock();
    double time_parallel = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Sorted Array: \n");
    for (int i = 0; i < ARRAY_SIZE; i++)
        printf("%d ", arr[i]);
    
    printf("\nExecution Time (Parallel): %f seconds\n", time_parallel);

    return 0;
}
