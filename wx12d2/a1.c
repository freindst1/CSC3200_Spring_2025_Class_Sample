#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

//number 1 to 100
//threads 0 to 9
//thread i will count from 10 * i + 1 to 10 * (i + 1)

int total_number = 109;
int thread_total = 10;
int sum = 0;

//let's pass the index i here
//this is the solution using partition methods
void * task(void * arg){
    //range from 10 * i + 1 to 10 * (i + 1)
    int index = *(int *)arg;
    int potion = total_number / thread_total;
    if (total_number % thread_total != 0){
        potion = potion + 1;
    }
    int start = potion * index + 1;
    int end = potion * (index + 1);
    if (index + 1 == thread_total){
        end = total_number;
    }
    while (start <= end){
        //sum = sum + start;
        printf("I am thread %d, and I am counting %d\n", index, start);
        start++;
    }
}

//let's make the round-robin algorithm here
void * task2(void *arg){
    int index = *(int *)arg;
    //for thread index == 0, all the number % total_thread == 0
    for(int i = 1; i <= total_number; i++){
        if (i % thread_total == index){
            printf("I am thread %d, and I am counting %d\n", index, i);
        }
    }
}


int main(){
    int ids[thread_total];
    for(int i = 0; i < thread_total; i++){
        ids[i] = i;
    }
    pthread_t threads[thread_total];

    for(int i = 0; i < thread_total; i++){
        pthread_create(&threads[i], NULL, task2, &ids[i]);
    }
    //main thread should wait for the sub thread
    for(int i = 0; i < thread_total; i++){
        pthread_join(threads[i], NULL);
    }

    return 0;
}