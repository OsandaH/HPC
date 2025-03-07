#include <stdio.h> 
#include <stdlib.h> 
#include <mpi.h> 

#define NUM_PROCESSES 4  

int arr[1000]; // Global array
int size; // Global variable for array size  

// Insertion Sort function  
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

// Merge function  
void merge(int arr[], int start, int mid, int end) {  
    int n1 = mid - start + 1;  
    int n2 = end - mid;  

    int *left = (int*)malloc(n1 * sizeof(int));  
    int *right = (int*)malloc(n2 * sizeof(int));  

    for (int i = 0; i < n1; i++)  
        left[i] = arr[start + i];  
    for (int j = 0; j < n2; j++)  
        right[j] = arr[mid + 1 + j];  

    int i = 0, j = 0, k = start;  
    while (i < n1 && j < n2) {  
        if (left[i] <= right[j])  
            arr[k++] = left[i++];  
        else  
            arr[k++] = right[j++];  
    }  

    while (i < n1) arr[k++] = left[i++];  
    while (j < n2) arr[k++] = right[j++];  

    free(left);  
    free(right);  
}  

int main(int argc, char** argv) {  
    int local_arr[] = {262,485,618,753,584,477,697,465,908,846,489,  
        324,659,324,552,604,775,498,393,758,424,44,12,866,891,675,  
        434,360,711,240,18,49,38,761,962,3,381,839,553,768,926,774,  
        545,46,541,231,670,660,218,536,945,134,804,552,747,964,922,614,  
        378,805,132,214,689,12};  

    size = sizeof(local_arr) / sizeof(local_arr[0]);  

    for (int i = 0; i < size; i++) {  
        arr[i] = local_arr[i];  
    }  

    int rank, num_processes;  
    double start_time, end_time;  

    MPI_Init(&argc, &argv);  
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);  
    MPI_Comm_size(MPI_COMM_WORLD, &num_processes);  

    if (num_processes != NUM_PROCESSES) {  
        if (rank == 0) {  
            printf("Error: Must run with %d processes.\n", NUM_PROCESSES);  
        }  
        MPI_Finalize();  
        return 1;  
    }  

    start_time = MPI_Wtime();  

    int local_size = size / num_processes;  
    int remainder = size % num_processes;  
    int *local_arr_part = (int*)malloc((local_size + 1) * sizeof(int));  

    int send_counts[num_processes];  
    int displacements[num_processes];  

    for (int i = 0; i < num_processes; i++) {  
        send_counts[i] = local_size + (i < remainder ? 1 : 0);  
        displacements[i] = (i == 0) ? 0 : (displacements[i - 1] + send_counts[i - 1]);  
    }  

    MPI_Scatterv(arr, send_counts, displacements, MPI_INT, local_arr_part, send_counts[rank], MPI_INT, 0, MPI_COMM_WORLD);  

    insertionSort(local_arr_part, 0, send_counts[rank] - 1);  

    MPI_Gatherv(local_arr_part, send_counts[rank], MPI_INT, arr, send_counts, displacements, MPI_INT, 0, MPI_COMM_WORLD);  

    if (rank == 0) {  
        for (int i = 1; i < num_processes; i++) {  
            int start_index = displacements[i];  
            int mid_index = start_index - 1;  
            int end_index = start_index + send_counts[i] - 1;  
            merge(arr, 0, mid_index, end_index);  
        }  

        printf("Sorted array:\n");  
        for (int i = 0; i < size; i++) {  
            printf("%d ", arr[i]);  
        }  
        printf("\n");  

        end_time = MPI_Wtime();  
        printf("Execution time (MPI): %f seconds\n", end_time - start_time);  
    }  

    free(local_arr_part);  
    MPI_Finalize();  

    return 0;  
}  
