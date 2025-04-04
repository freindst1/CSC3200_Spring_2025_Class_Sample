#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void handle(){
    printf("exit\n");
    exit(1);
}

int main(){
    signal(SIGINT, handle);
    while(1);
    return 0;
}