#include <stdio.h>
#include <iostream>
#include <math.h>
#include <pthread.h>
#include <stdlib.h>

#define N_THREADS 4
#define BARRIER_NUM 3

pthread_barrier_t barrier;
void *thread_func(void *arg){
    int id = *(int*) arg;
    printf("Thread %d strated\n",id);
    pthread_barrier_wait(&barrier);
    printf("Thread %d after barrier\n",id);
    return NULL;
}

int main(){
    pthread_t threads[N_THREADS];
    int ids[N_THREADS];
    int i;

    pthread_barrier_init(&barrier,NULL, BARRIER_NUM);

    for(i=0; i <N_THREADS; i++){
        ids[i] = i;
        pthread_create(&threads[i], NULL, &thread_func, &ids[i]);
    }
    for(i = 0; i < N_THREADS; i++){
        pthread_join(threads[i], NULL);
    }
    pthread_barrier_destroy(&barrier);

    return 0;
}
