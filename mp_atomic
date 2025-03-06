#include <omp.h>
#include <stdio.h>

int main(){

    // atomic

    // int sharedsum = 0;
    // const int numIterations = 100;

    // #pragma omp parallel for
    // for (int i = 0; i < numIterations; i++){
    //     #pragma omp atomic 
    //     sharedsum += i;
    // }
    // printf("SharedSum = %d \n", sharedsum);

    // return 0;

    // //atomic write 
    // int counter = 0;
    // #pragma omp parallel num_threads(4)
    // {
    //     #pragma omp atomic write
    //     counter = 100;

    //     printf("Counter: %d\n", counter);
    
    // }

    // //atomic update 
    // int counter = 0;
    // #pragma omp parallel num_threads(4)
    // {
    //     #pragma omp atomic update
    //     counter += omp_get_thread_num();
    //     printf("Counter: %d\n", counter);

    // }

    // //atomic read 
    // int counter1 = 42;
    // int value;
    // #pragma omp parallel num_threads(4)
    // {
    //     #pragma omp atomic read
    //     value = counter1;
    
    //     printf("Counter: %d\n", value);

    // }

    int counter = 42;
    int result;
    #pragma omp parallel num_threads(4)
    {
        int incremate = 5;
        #pragma omp atomic capture
        result = counter += incremate;

        printf("Value: %d\n", result);
    }

    return 0;


}
