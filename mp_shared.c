#include <omp.h>
#include <stdio.h>

#define NUM_THREADS 4

int main(){
    int x = 42;
    omp_set_num_threads(NUM_THREADS);

    // Shared Vaiable 
    printf("Shared\n");
    #pragma omp parallel shared(x)
    {
        x = x + 1;
        printf("Thread %d: x = %d \n",omp_get_thread_num(), x);
    }
    printf("Final x = %d\n",x);


    // First Private Variable 
    printf("first private\n");
    #pragma omp parallel firstprivate(x)
    {
        x = x + 1;
        printf("Thread %d: x = %d \n",omp_get_thread_num(), x);
    }
    printf("Final x = %d\n\n",x);


    //Last Private variable 
    int y = 0;
    printf("Last private\n");
    #pragma omp parallel for lastprivate(y)
    for(int i = 0; i < 5; i++){
        x = i; 
        printf("Thread %d: x = %d\n",omp_get_thread_num(),x);
    }
    printf("Final x = %d\n",x); // x retains the value from the last iteration 




    return 0;
}
