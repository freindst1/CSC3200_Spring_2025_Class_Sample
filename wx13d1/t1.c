#include <pthread.h>
#include <stdio.h>

int counter = 0;                   // Shared data
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void* increment(void* arg) {
    for (int i = 0; i < 100000; i++) {
        pthread_mutex_lock(&lock);   // Lock before accessing shared data
        counter++;                   // Critical section
        pthread_mutex_unlock(&lock); // Unlock after done
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;
    pthread_create(&t1, NULL, increment, NULL);
    pthread_create(&t2, NULL, increment, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Final counter: %d\n", counter); // Should be 200000
    pthread_mutex_destroy(&lock);
    return 0;
}