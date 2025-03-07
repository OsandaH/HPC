#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size, n;
    long long local_factorial = 1;
    long long global_factorial = 1;

    // Initialize MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        // Input the number of integers to sum (factorial)
        printf("Enter the number for factorial: ");
        scanf("%d", &n);
    }

    // Broadcast n to all processes
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Calculate local factorial for this process
    int segment_size = n / size;
    int start = rank * segment_size + 1;
    int end = (rank == size - 1) ? n : (rank + 1) * segment_size;

    for (int i = start; i <= end; i++) {
        local_factorial *= i;
    }

    // Use MPI_Reduce to combine the local factorials into the global factorial
    MPI_Reduce(&local_factorial, &global_factorial, 1, MPI_LONG_LONG, MPI_MULTIPLY, 0, MPI_COMM_WORLD);

    // Only process 0 will print the result
    if (rank == 0) {
        printf("The factorial of %d! is %lld\n", n, global_factorial);
    }

    // Finalize MPI
    MPI_Finalize();

    return 0;
}
