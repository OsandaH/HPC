//serianl
#include <stdio.h>

int main() {
    // Given array
    int arr[] = {262,485,618,753,584,477,697,465,908,846,489,
        324,659,324,552,604,775,498,393,758,424,44,12,866,891,675,
        434,360,711,240,18,49,38,761,962,3,381,839,553,768,926,774,
        545,46,541,231,670,660,218,536,945,134,804,552,747,964,922,614,
        378,805,132,214,689,12};
    
    int size = sizeof(arr) / sizeof(arr[0]);  // Compute array size
    int target = 541;  // Number to search for
    int found = 0;      // Flag to check if found

    // Linear search
    for (int i = 0; i < size; i++) {
        if (arr[i] == target) {
            printf("Number %d found at index %d.\n", target, i);
            found = 1;
            break; // Stop searching once found
        }
    }

    if (!found) {
        printf("Number %d not found in the array.\n", target);
    }

    return 0;
}

//pthread
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define ARRAY_SIZE 65   // Total elements in the array
#define NUM_THREADS 4   // Number of threads
#define TARGET 541      // Number to search

int arr[] = {262,485,618,753,584,477,697,465,908,846,489,
    324,659,324,552,604,775,498,393,758,424,44,12,866,891,675,
    434,360,711,240,18,49,38,761,962,3,381,839,553,768,926,774,
    545,46,541,231,670,660,218,536,945,134,804,552,747,964,922,614,
    378,805,132,214,689,12};

pthread_t threads[NUM_THREADS];
int found = 0; // Shared flag to indicate target found
pthread_mutex_t lock; // Mutex for thread synchronization

// Structure to pass arguments to threads
typedef struct {
    int thread_id;
    int start;
    int end;
} ThreadArgs;

// Thread function to search for the number
void* search(void* arg) {
    ThreadArgs* args = (ThreadArgs*) arg;

    for (int i = args->start; i < args->end; i++) {
        if (arr[i] == TARGET) {
            pthread_mutex_lock(&lock);
            if (!found) { // Prevent duplicate prints
                printf("Number %d found at index %d by thread %d.\n", TARGET, i, args->thread_id);
                found = 1; // Set flag to stop other threads
            }
            pthread_mutex_unlock(&lock);
            break;
        }
    }
    pthread_exit(NULL);
}

int main() {
    pthread_mutex_init(&lock, NULL);
    ThreadArgs thread_args[NUM_THREADS];
    int segment_size = ARRAY_SIZE / NUM_THREADS;

    // Create threads
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_args[i].thread_id = i;
        thread_args[i].start = i * segment_size;
        thread_args[i].end = (i == NUM_THREADS - 1) ? ARRAY_SIZE : (i + 1) * segment_size;
        pthread_create(&threads[i], NULL, search, (void*)&thread_args[i]);
    }

    // Wait for threads to complete
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    if (!found) {
        printf("Number %d not found in the array.\n", TARGET);
    }

    pthread_mutex_destroy(&lock);
    return 0;
}

//openMP
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define ARRAY_SIZE 65   // Total elements in the array
#define TARGET 541      // Number to search

int arr[] = {262,485,618,753,584,477,697,465,908,846,489,
    324,659,324,552,604,775,498,393,758,424,44,12,866,891,675,
    434,360,711,240,18,49,38,761,962,3,381,839,553,768,926,774,
    545,46,541,231,670,660,218,536,945,134,804,552,747,964,922,614,
    378,805,132,214,689,12};

int found = 0; // Shared flag to indicate target found

// Function to search for the number
void search(int start, int end) {
    for (int i = start; i < end; i++) {
        if (arr[i] == TARGET) {
            #pragma omp critical
            {
                if (!found) { // Prevent duplicate prints
                    printf("Number %d found at index %d.\n", TARGET, i);
                    found = 1; // Set flag to stop other threads
                }
            }
            break;
        }
    }
}

int main() {
    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        int num_threads = omp_get_num_threads();
        int segment_size = ARRAY_SIZE / num_threads;
        int start = thread_id * segment_size;
        int end = (thread_id == num_threads - 1) ? ARRAY_SIZE : (thread_id + 1) * segment_size;

        search(start, end);

        // Prevent unnecessary prints after the target is found
        #pragma omp flush(found)
    }

    if (!found) {
        printf("Number %d not found in the array.\n", TARGET);
    }

    return 0;
}

//OpenMPI

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define ARRAY_SIZE 65   // Total elements in the array
#define TARGET 541      // Number to search
#define NUM_PROCESSES 4 // Number of processes

int arr[] = {262,485,618,753,584,477,697,465,908,846,489,
    324,659,324,552,604,775,498,393,758,424,44,12,866,891,675,
    434,360,711,240,18,49,38,761,962,3,381,839,553,768,926,774,
    545,46,541,231,670,660,218,536,945,134,804,552,747,964,922,614,
    378,805,132,214,689,12};

int main(int argc, char *argv[]) {
    int rank, size;
    int segment_size;
    int start, end;
    int found = 0; // Flag to indicate the target has been found

    // Initialize MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Each process will handle a portion of the array
    segment_size = ARRAY_SIZE / size;
    start = rank * segment_size;
    end = (rank == size - 1) ? ARRAY_SIZE : (rank + 1) * segment_size;

    // Search for the target within the assigned segment
    for (int i = start; i < end; i++) {
        if (arr[i] == TARGET) {
            printf("Number %d found at index %d by process %d.\n", TARGET, i, rank);
            found = 1;
            break;
        }
    }

    // Use MPI to broadcast the found flag to all processes
    MPI_Bcast(&found, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Only the first process (rank 0) will check the result
    if (rank == 0 && found == 0) {
        printf("Number %d not found in the array.\n", TARGET);
    }

    // Finalize MPI
    MPI_Finalize();
    return 0;
}
