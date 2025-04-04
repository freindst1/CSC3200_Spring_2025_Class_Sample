#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

int sum = 0;
int total = 100;
int thread_total = 10;

pthread_mutex_t lock;

struct range{
    int start;
    int end;
};

void *add(void *arg){
    struct range* ra = (struct range *)arg;
    int k = ra->start;
    printf("count range from %d to %d.\n", ra->start, ra->end);
    while (k <= ra->end){
        pthread_mutex_lock(&lock);
        sum += k;
        pthread_mutex_unlock(&lock);
        k++;
    }
}

int main(){
    pthread_mutex_init(&lock, NULL);
    int t = 0;
    pthread_t threads[thread_total]; 
    int ratio = total / thread_total;
    for(int i = 0; i < thread_total; i++){
        struct range r;
        r.start = i * ratio;
        if (i < total - 1){
            r.end = (i + 1) * ratio - 1;
        } else {
            r.end = total;
        }
        printf("assign job from %d to %d\n", r.start, r.end);
        pthread_create(&threads[i], NULL, add, &r);
    }
    for(int i = 0; i < thread_total; i++){
        pthread_join(threads[i], NULL);
    }
    printf("total sum is %d\n", sum);
    pthread_mutex_destroy(&lock);
    return 0;
}
