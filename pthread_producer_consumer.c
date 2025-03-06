#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h> // For sleep // this adds a delay for each calculation

#define BUFFER_SIZE 5
#define MAX_VELOCITY 70
#define NUM_READINGS 10

int buffer[BUFFER_SIZE];   // Shared buffer to store velocities
int count = 0;             // Number of items in the buffer

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t not_full = PTHREAD_COND_INITIALIZER;
pthread_cond_t not_empty = PTHREAD_COND_INITIALIZER;

void *producer(void *arg) {
    for (int i = 0; i < NUM_READINGS; i++) {
		
        int velocity = rand() % (MAX_VELOCITY + 1); 
		
        pthread_mutex_lock(&mutex); 
		
        while (count == BUFFER_SIZE) {
            pthread_cond_wait(&not_full, &mutex);
        }

        buffer[count++] = velocity;
        printf("Produced velocity: %d km/h\n", velocity);

        pthread_cond_signal(&not_empty);

        pthread_mutex_unlock(&mutex);

        sleep(1); // this pauses execussion for 1 second.
    }
    pthread_exit(NULL);
}

void *consumer(void *arg) {
    for (int i = 0; i < NUM_READINGS; i++) {
        pthread_mutex_lock(&mutex); 

        while (count == 0) {
            pthread_cond_wait(&not_empty, &mutex);
        }

        int velocity = buffer[--count];
        printf("Consumed velocity: %d km/h\n", velocity);

        pthread_cond_signal(&not_full);

        pthread_mutex_unlock(&mutex); 

        static int total_velocity = 0; 
        static int readings = 0;     

        total_velocity += velocity;
        readings++;

        double average_velocity = (double)total_velocity / readings;
        printf("Average velocity after %d readings: %.2f km/h\n", readings, average_velocity);
    }
    pthread_exit(NULL);
}


int main() {
    pthread_t producer_thread, consumer_thread;

    srand(time(NULL)); 
	
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    return 0;
}
