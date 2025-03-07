
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>


#define VECTOR_SIZE 12

int main(int argc, char **argv){
    MPI_Init(&argc, &argv);

    int rank, size;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(size < 2){
        fprintf(stderr, "This Program Requires at least 2 MPI processes.\n");
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    if(VECTOR_SIZE % size != 0){
        fprintf(stderr, "Vector size must be divisible by the number of processes.\n");
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    int *x = NULL;
    int *y = NULL;
    int *local_x = NULL;
    int *local_y = NULL;
    int local_dot_product = 0;
    int *partial_results = NULL;

    if (rank == 0){
        // Initialize vectors on the root process
        x = (int*)malloc(sizeof(int) * VECTOR_SIZE);
        y = (int*)malloc(sizeof(int) * VECTOR_SIZE);

        partial_results = (int*)malloc(sizeof(int)*size);

        // Initialize vectors with some values (for demonstration purposes)
        for (int i = 0; i < VECTOR_SIZE; ++i) {
            x[i] = i + 1;
            y[i] = (i + 1) * 2;
        }
    }
    // Scatter the vectors to all processes
    local_x = (int*)malloc(sizeof(int) * VECTOR_SIZE / size);
    local_y = (int*)malloc(sizeof(int) * VECTOR_SIZE / size);
    
    MPI_Scatter(x, VECTOR_SIZE / size, MPI_INT, local_x, VECTOR_SIZE / size, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(y, VECTOR_SIZE / size, MPI_INT, local_y, VECTOR_SIZE / size, MPI_INT, 0, MPI_COMM_WORLD);

    // Perform element-wise addition on local portions
    for (int i = 0; i < VECTOR_SIZE / size; ++i) {
        local_dot_product += local_x[i] * local_y[i];
    }

    // Gather the results back to the root process
    MPI_Gather(&local_dot_product, 1, MPI_INT, partial_results, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Print the final result on the root process
    if (rank == 0) {
        int global_dot_product = 0;
        for (int i = 0; i < size; ++i) {
            global_dot_product += partial_results[i];
        }
        printf("Dot Product: %d\n", global_dot_product);   
    }
    free(x);
    free(y);
    free(local_x);
    free(local_y);
    free(partial_results);

    MPI_Finalize();
    return 0;  

}
