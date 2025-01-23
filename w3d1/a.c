#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main(){
    int fd;
    //int open(const char *name, int flags);
    int fd = open("file1.txt", O_CREAT);

    if (fd == -1){
        printf("file create errors.");
    }

    printf("%d", fd);
    //power outage happens
    close(fd);
    //power outage
    return 0;
}