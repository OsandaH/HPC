//reduce_max_min.c
#include <stdio.h>
#include <mpi.h>
#include <limits.h>

int main(int argc, char** argv){
    
    MPI_Init(&argc, &argv);

    int rank, size, local_max, global_max;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    int array[] = {3,2,1,1,-3,100,150};
    int local_value = 0;
    int array_size = sizeof(array)/sizeof(array[0]);

    if(rank < array_size){
        local_value = array[rank];
    }else {
        local_value = INT_MIN; // Smallest possible integer to avoid affecting max operation
    }
    MPI_Reduce(&local_value, &global_max, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);

    if(rank == 0){
        printf("Gloabal Max: %d\n",global_max);
    }
    MPI_Finalize();

    return 0;
}

