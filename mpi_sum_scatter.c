#include <stdio.h> 
#include <mpi.h> 
 
int main(int argc, char** argv) { 
    MPI_Init(&argc, &argv); 
 
    int rank, size; 
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
    MPI_Comm_size(MPI_COMM_WORLD, &size); 
 
    int array[] = {23, 45, 67, 12, 89, 34, 56, 78, 90, 11, 45, 67, 89, 12, 34, 56, 78, 
90, 11, 23, 67, 89, 12, 34, 56, 78, 90, 11,23, 45, 89, 12, 34, 56, 78, 90, 11, 23, 45, 
67, 12, 34, 56, 78, 90, 11, 23, 45, 67, 89, 34, 56, 78, 90, 11, 23, 45, 67, 89, 12, 
56, 78, 90, 11, 23, 45, 67, 89, 12, 34, 78, 90, 11, 23, 45, 67, 89, 12, 34, 56, 90, 
11, 23, 45,67, 89, 12, 34, 56, 78, 11, 23, 45, 67, 89, 12, 34, 56, 78, 90}; 
 
    int array_size = sizeof(array) / sizeof(array[0]); 
    int chunk_size = array_size / size; 
    int local_array[chunk_size]; 
 
    MPI_Scatter(array, chunk_size, MPI_INT, local_array, chunk_size, MPI_INT, 0, 
MPI_COMM_WORLD); 
 
    int local_sum = 0; 
    for (int i = 0; i < chunk_size; i++) { 
        local_sum += local_array[i]; 
    } 
 
    int global_sums[size]; 
    MPI_Gather(&local_sum, 1, MPI_INT, global_sums, 1, MPI_INT, 0, MPI_COMM_WORLD); 
 
    double global_sum = 0; 
    if (rank == 0) { 
        for (int i = 0; i < size; i++) { 
            global_sum += global_sums[i]; 
        } 
        double Avg = global_sum / array_size; 
        printf("Average: %.3f\n", Avg); 
    } 
    MPI_Finalize(); 
    return 0; 
} 
