#include <iostream>
#include <math.h>
#include <pthread.h>

#define NUM_THREADS 4

void *thread_function(void *arg){
    int *id_ptr = (int*) arg;
    printf("Thread %d say hello \n", *id_ptr);
    return NULL;
}

int main(){
    /*
    // creating and joining a thread
    pthread_t my_thread;
    int thread_id = 1;
    printf("before thread creation \n");
    pthread_create(&my_thread, NULL, thread_function, &thread_id);
    printf("after thread creation \n");
    pthread_join(my_thread, NULL);
    printf("after thread join \n");
    return 0;
    */
    

    // creating and joining multiple threads
    // gets different outputs in each run
    
    pthread_t threads[NUM_THREADS];
    int threads_ids[NUM_THREADS];
    int i;
    for(i=0; i<NUM_THREADS; i++){
        threads_ids[i] = i;
        pthread_create(&threads[i], NULL, thread_function, &threads_ids[i]);
    }

    for(i = 0; i <NUM_THREADS; i++){
        pthread_join(threads[i],NULL);
    }
    return 0;


}
