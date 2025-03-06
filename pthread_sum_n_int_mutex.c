#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 4 

pthread_t threads[NUM_THREADS];
int shared_sum = 0;
pthread_mutex_t mutex;

int N;

void* thread_function(void* arg) {
    int thread_id = *(int*)arg;  
    
	int size = N / NUM_THREADS;
	int local_start = thread_id * size + 1;
	int local_end;

	if (thread_id == NUM_THREADS - 1) {
		local_end = N;
	} else {
		local_end = (thread_id + 1) * size;
	}

	int local_sum = 0;

    for (int i = local_start; i <= local_end; i++) {
        local_sum += i;
    }

    pthread_mutex_lock(&mutex);
    shared_sum += local_sum;
    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main() {
	printf("Enter the value of N: ");
	scanf("%d",&N);
	
    int thread_ids[NUM_THREADS];
    pthread_mutex_init(&mutex, NULL); 
	
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, thread_function, &thread_ids[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex); 
	
    printf("The summation of the first %d integers is: %d\n", N, shared_sum);

    return 0;
}
