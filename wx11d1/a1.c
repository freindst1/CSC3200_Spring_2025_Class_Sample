#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void handler(int sig, siginfo_t *info, void *context){
    printf("I got a signal, and the payload int is %d.\n", info->si_value.sival_int);
}


int main(){
    int pid = fork();

    if (pid == 0){
        //child
        //signal(SIGUSR1, handler);
        struct sigaction sa;
        sa.sa_flags = SA_SIGINFO;
        sa.sa_sigaction = handler;
        sigaction(SIGUSR1, &sa, NULL);
        while(1){
            pause();
            exit(0);
        }
    } else {
        //parent
        sleep(1);
        //kill(pid, SIGUSR1);
        union sigval si;
        si.sival_int = 325;
        sigqueue(pid, SIGUSR1, si);
    }

    return 0;
}