#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_THREADS 10
#define NUM_INCREMENTS 1000000

int counter = 0;
sem_t semaphore;

void* increment_counter(void* arg) {
    for (int i = 0; i < NUM_INCREMENTS; i++) {
        sem_wait(&semaphore);   // Wait (lock the semaphore)
        counter++;
        sem_post(&semaphore);   // Signal (unlock the semaphore)
    }
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];

    // Initialize semaphore
    sem_init(&semaphore, 0, 1);

    // Create threads
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, increment_counter, NULL);
    }

    // Wait for all threads to finish
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Final counter value (with semaphore): %d\n", counter);

    // Destroy semaphore
    sem_destroy(&semaphore);

    return 0;
}
