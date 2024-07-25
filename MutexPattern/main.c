#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 4
#define ITERATIONS 1000000

int counter = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *thread_function(void *arg) {
    for (int i = 0; i < ITERATIONS; ++i) {
        pthread_mutex_lock(&mutex); // Lock mutex before critical section
        counter++;
        pthread_mutex_unlock(&mutex); // Unlock mutex after critical section
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; ++i) {
        if (pthread_create(&threads[i], NULL, thread_function, NULL) != 0) {
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < NUM_THREADS; ++i) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("pthread_join");
            exit(EXIT_FAILURE);
        }
    }

    printf("Correct result with mutex: Counter is %d (expected %d)\n", counter, NUM_THREADS * ITERATIONS);

    // Destroy the mutex
    pthread_mutex_destroy(&mutex);

    return 0;
}
