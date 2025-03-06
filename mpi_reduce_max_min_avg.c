#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv){
    MPI_Init(&argc, &argv);

    int rank, size, local_max, global_max, local_min, global_min;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int array[] = {23, 45, 67, 12, 89, 34, 56, 78, 90, 11, 45, 67, 89, 12, 34, 56, 78, 90, 11, 23, 67, 89, 12, 34, 56, 78, 90, 11,
                    23, 45, 89, 12, 34, 56, 78, 90, 11, 23, 45, 67, 12, 34, 56, 78, 90, 11, 23, 45, 67, 89, 34, 56, 78, 90, 11, 23,
                    45, 67, 89, 12, 56, 78, 90, 11, 23, 45, 67, 89, 12, 34, 78, 90, 11, 23, 45, 67, 89, 12, 34, 56, 90, 11, 23, 45,
                    67, 89, 12, 34, 56, 78, 11, 23, 45, 67, 89, 12, 34, 56, 78, 90};
    
    
    int array_size = sizeof(array) / sizeof(array[0]);
    int chunk_size = array_size / size;

    // Maximum Value 
    local_max = array[rank * chunk_size];
    for (int i = rank * chunk_size + 1; i < (rank + 1) * chunk_size; i++) {
        if (i < array_size && array[i] > local_max) {
            local_max = array[i];
        }
    }
    MPI_Reduce(&local_max, &global_max, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);


    // Minimum value
    local_min = array[rank * chunk_size];
    for (int i = rank * chunk_size + 1; i < (rank + 1) * chunk_size; i++) {
        if (i < array_size && array[i] < local_min) {
            local_min = array[i];
        }
    }
    MPI_Reduce(&local_min, &global_min, 1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);


    // Average 
    int local_sum = 0;
    int global_sum = 0;

    for(int i = rank; i < array_size; i+= size){
        local_sum += array[i];
    }
    
    MPI_Reduce(&local_sum, &global_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    

    double Avg = (double)global_sum/array_size;

    if(rank == 0){

        printf("Maximum Value: %d\n",global_max);
        printf("Minimum Value: %d\n",global_min);        
        printf("Average: %.3f\n",Avg);
        
    }

    // MPI_Bcast(&global_max, 1, MPI_INT, 0, MPI_COMM_WORLD);
    // MPI_Bcast(&global_min, 1, MPI_INT, 0, MPI_COMM_WORLD);
    // MPI_Bcast(&Avg, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // //double theta = (global_max- global_min)* rank + Avg/2;

    //  double theta = (local_sum);//- global_min)* rank + Avg/2;

    
    // printf("Process %d has Theta=  %.3f\n",rank,theta);
    
    MPI_Finalize();
    return 0;

}
