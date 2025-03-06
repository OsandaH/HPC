//intSumMPI_reduce.c

#include <stdio.h>
#include <mpi.h>

int main(){
    MPI_Init(NULL,NULL);
    int world_rank, world_size;

    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int array[] = {5,3,2,6,1,-3,-6,10};
    int local_sum = 0;
    int total_sum = 0;

    //using MPI_Reduce
    
    for(int i = world_rank; i < sizeof(array)/sizeof(array[0]); i += world_size){
        local_sum += array[i];
    }
    MPI_Reduce(&local_sum, &total_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    
    if(world_rank == 0){
        printf("The toatal sum is = %d\n",total_sum);
    }
    MPI_Finalize();
    return 0;
    
}
