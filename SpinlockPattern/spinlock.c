#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int counter = 0;  // Shared resource
volatile int lock = 0;  // Spinlock flag (volatile to prevent optimizations)

void acquire_lock(int* lock_ptr)
{
    while (__sync_val_compare_and_swap(lock_ptr, 0, 1) != 0) {
        // Busy waiting until lock becomes available
    }
}

void release_lock(int* lock_ptr)
{
    *lock_ptr = 0;
}

void* increment(void* arg) {
    for (int i = 0; i < 100000; i++)
    {
        acquire_lock(&lock);
        counter++;  // Now protected by spinlock
        release_lock(&lock);
        usleep(1);   // Simulate some work
    }
    return NULL;
}

int main() {
    pthread_t threads[2];

    // Create threads
    for (int i = 0; i < 2; i++) {
        if (pthread_create(&threads[i], NULL, increment, NULL) != 0) {
            perror("pthread_create failed");
            return 1;
        }
    }

    // Wait for threads to finish
    for (int i = 0; i < 2; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("pthread_join failed");
            return 1;
        }
    }

    printf("Final counter value (expected 200000): %d\n", counter);
    return 0;
}
