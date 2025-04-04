#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>


void *speak(void *arg){
    //int *a = (int *)arg;
    sleep(1);
    printf("A thread revokes this speak function. the function passed in a value: %d\n", *(int *)arg);
}

int main(){
    //speak();
    pthread_t t_id;
    int f = 10;
    int *p = &f;
    pthread_create(&t_id, NULL, speak, p);
    printf("new thread id is %ld.\n", t_id);
    //sleep(1); //make the main thread to wait, without trigger the return too early
    pthread_join(t_id, NULL);
    //who is waiting? main thread/process
    //waiting for what? new created thread
    //how many processes are there? 1
    //how many threads are there?   2
    return 0;   //kill process
    //how many processes?   0?
    //how many threads?     0?
}