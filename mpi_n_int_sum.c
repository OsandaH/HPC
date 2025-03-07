#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size;
    int local_sum = 0, global_sum = 0;

    // Initialize MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Define the range for each process to handle
    int n = 1000;
    int segment_size = n / size;
    int start = rank * segment_size + 1;
    int end = (rank == size - 1) ? n : (rank + 1) * segment_size;

    // Calculate the local sum for this process
    for (int i = start; i <= end; i++) {
        local_sum += i;
    }

    // Use MPI_Reduce to sum up the local sums from all processes
    MPI_Reduce(&local_sum, &global_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    // Only the root process (rank 0) will print the final result
    if (rank == 0) {
        printf("Sum of the first 1000 integers: %d\n", global_sum);
    }

    // Finalize MPI
    MPI_Finalize();

    return 0;
}
