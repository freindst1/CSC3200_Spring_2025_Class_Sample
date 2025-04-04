#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

int pids[5];
int n = 0;
int ppid = 0;

// Signal handler function
void child_handle_signal(int sig, siginfo_t *info, void *context) {
    printf("Child received signal: %d with payload: %d\n", sig, info->si_value.sival_int);
    int val = info->si_value.sival_int;
    if (val == 0){
        printf("No child left. Child exiting...\n");
        exit(0);
    } else {
        printf("The next child process is %d. Child quit.\n", val);
        kill(ppid, SIGUSR1);
        exit(0);
    }
}

void parent_handle_singal(){
    printf("Parent received signal\n");
}

int main(){
    ppid = getpid();
    struct sigaction sa;
    sa.sa_flags = SA_SIGINFO;  // Use SA_SIGINFO to receive payload
    sa.sa_sigaction = child_handle_signal;  // Assign signal handler
    for(int i = 0; i < 5; i++){
        int pid = fork();
        if(pid == 0){
            //child
            sigaction(SIGUSR1, &sa, NULL);
            for(;;){
                pause();
            }
            exit(0);
        } else {
            //parent
            pids[i] = pid;
        }
    }
    sleep(2);
    union sigval payload;
    for(int i = 0; i < 5; i++){
        if (i < 5){
            payload.sival_int = pids[i+1];
        } else{
            payload.sival_int = 0;
        }
        if (sigqueue(pids[i], SIGUSR1, payload) < 0) {
            perror("sigqueue failed");
            exit(1);
        }
        if (i < 4){
            signal(SIGUSR1, parent_handle_singal);
            pause();
        }
    }
    sleep(6);
    printf("Parent exiting...\n");
    return 0;
}