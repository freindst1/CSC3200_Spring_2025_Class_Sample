#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

// Signal handler function
void handle_signal(int sig, siginfo_t *info, void *context) {
    printf("Child received signal: %d with payload: %d\n", sig, info->si_value.sival_int);
}

int main() {
    struct sigaction sa;
    pid_t pid = fork();  // Create child process

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }

    if (pid == 0) {
        // Child process: Set up signal handler
        sa.sa_flags = SA_SIGINFO;  // Use SA_SIGINFO to receive payload
        sa.sa_sigaction = handle_signal;  // Assign signal handler
        sigaction(SIGUSR1, &sa, NULL);

        printf("Child process waiting for signal...\n");
        while (1) {
            pause();  // Wait for signals
        }
    } else {
        // Parent process
        sleep(2); // Allow child to set up handler

        printf("Parent sending SIGUSR1 with payload to child (PID: %d)\n", pid);
        
        union sigval payload;
        payload.sival_int = 42;  // Custom payload data
        
        // Send signal with payload
        if (sigqueue(pid, SIGUSR1, payload) < 0) {
            perror("sigqueue failed");
            exit(1);
        }

        sleep(1); // Allow time for child to receive signal
        printf("Parent exiting...\n");
    }

    return 0;
}