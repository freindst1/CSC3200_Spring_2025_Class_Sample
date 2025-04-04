#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

int main(){
    int fd[2];
    pipe(fd);
    int pid = fork();
    if (pid == 0){  //this is the child process from fork()
        printf("I am the child.\n");
        char * buffer = malloc(6);
        read(fd[0], buffer, 6);
        printf("The pipe contains %s.\n", buffer);
        free(buffer);
    } else {
        printf("I am the father.\n");
        write(fd[1], "hello", 6);
    }
    return 0;
}