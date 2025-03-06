#include <stdlib.h>
#include <stdio.h>   
#include <pthread.h> 
#include <time.h> 


#define NUM_THREADS 4 
#define TOTAL_POINTS 100000000 

double global_count = 0.0; 
pthread_mutex_t lock; 

void *monte_carlo(void *thread_id){
	int tid = *((int*)thread_id);
	
	int points_per_thread = TOTAL_POINTS/NUM_THREADS;
	
	int local_count = 0;
	
	srand((unsigned int)time(NULL)+ tid);
	
	for(int i = 0; i < points_per_thread; i++){
		double x = (double)rand() / RAND_MAX; 
		double y = (double)rand() / RAND_MAX; 
		double dist = x*x + y*y; 
		
		if (dist <= 1.0){ 
		
			local_count++;
			
		}
	}
	pthread_mutex_lock(&lock);
	
	global_count += local_count;
	
	pthread_mutex_unlock(&lock);
	
	pthread_exit(NULL); 
}

int main (){
	pthread_t threads[NUM_THREADS]; 
	int thread_ids[NUM_THREADS];   
	
	pthread_mutex_init(&lock, NULL); 
	
	for (int i = 0; i < NUM_THREADS; i++){  
		thread_ids[i] = i;
		
		
		pthread_create(&threads[i], NULL, monte_carlo, &thread_ids[i]);
		
		
	}
	for (int i = 0; i < NUM_THREADS; i++){ 
		pthread_join(threads[i], NULL);

	}
	pthread_mutex_destroy(&lock);
	
	double pi = 4.0 * (global_count / TOTAL_POINTS);
	
	printf("Estimated pi value: %f\n",pi);
	
	return 0;
	
	
}
