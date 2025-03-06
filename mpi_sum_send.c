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

    //using MPI_Send and MPI_Recv
    
    for(int i = world_rank; i < sizeof(array)/sizeof(array[0]); i += world_size){
        local_sum += array[i];
    }
    if(world_rank != 0){
        MPI_Send(&local_sum, 1,MPI_INT, 0, 0, MPI_COMM_WORLD);
    }
    else{
        total_sum = local_sum;
        for(int source = 1; source <world_size; ++source){
            int recieved_sum;
            MPI_Recv(&recieved_sum, 1, MPI_INT,source, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            total_sum +=recieved_sum;
        }
    }
    if(world_rank == 0){
        printf("The toatal sum is = %d\n",total_sum);
    }
    MPI_Finalize();
    return 0;
    
}
