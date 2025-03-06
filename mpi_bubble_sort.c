#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void merge(int **local_arr, int *local_n, int recv_arr[], int recv_n) {
    int *temp = (int *)malloc((*local_n + recv_n) * sizeof(int));
    int i = 0, j = 0, k = 0;
    
    while (i < *local_n || j < recv_n) {
        if (j >= recv_n || (i < *local_n && (*local_arr)[i] < recv_arr[j]))
            temp[k++] = (*local_arr)[i++];
        else
            temp[k++] = recv_arr[j++];
    }

    free(*local_arr);
    *local_arr = temp;
    *local_n += recv_n;
}

int main(int argc, char *argv[]) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int arr[] = {23, 45, 67, 12, 89, 34, 56, 78, 90, 11, 45, 67, 89, 12, 34, 56, 78, 90, 11, 23, 67, 89, 12, 34,
                 56, 78, 90, 11, 23, 45, 89, 12, 34, 56, 78, 90, 11, 23, 45, 67, 12, 34, 56, 78, 90, 11, 23, 45,
                 67, 89, 34, 56, 78, 90, 11, 23, 45, 67, 89, 12, 56, 78, 90, 11, 23, 45, 67, 89, 12, 34, 78, 90,
                 11, 23, 45, 67, 89, 12, 34, 56, 90, 11, 23, 45, 67, 89, 12, 34, 56, 78, 11, 23, 45, 67, 89, 12,
                 34, 56, 78, 90};
    int n = sizeof(arr) / sizeof(arr[0]);
    int local_n = n / size;
    int *local_arr = (int *)malloc(local_n * sizeof(int));

    MPI_Scatter(arr, local_n, MPI_INT, local_arr, local_n, MPI_INT, 0, MPI_COMM_WORLD);

    bubbleSort(local_arr, local_n);

    for (int step = 1; step < size; step *= 2) {
        if (rank % (2 * step) == 0) {
            if (rank + step < size) {
                int recv_n;
                MPI_Recv(&recv_n, 1, MPI_INT, rank + step, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                int *recv_arr = (int *)malloc(recv_n * sizeof(int));
                MPI_Recv(recv_arr, recv_n, MPI_INT, rank + step, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                merge(&local_arr, &local_n, recv_arr, recv_n);
                free(recv_arr);
            }
        } else {
            int target = rank - step;
            MPI_Send(&local_n, 1, MPI_INT, target, 0, MPI_COMM_WORLD);
            MPI_Send(local_arr, local_n, MPI_INT, target, 1, MPI_COMM_WORLD);
            break;
        }
    }

    if (rank == 0) {
        printf("Sorted array:\n");
        for (int i = 0; i < local_n; i++) {
            printf("%d ", local_arr[i]);
        }
        printf("\n");
    }

    free(local_arr);
    MPI_Finalize();
    return 0;
}
