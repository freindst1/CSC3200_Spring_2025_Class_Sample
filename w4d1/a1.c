#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(){
    int fd;
    fd = open("file.txt", O_RDONLY);

    ssize_t nr;

    char arr[8];

    nr = read(fd, arr, 8);

    printf("%d\n", (int)nr); //it should be 8
    printf("%s\n", arr); //it should be 12345678

    nr = read(fd, arr, 8);

    printf("%d\n", (int)nr); //it should be 1
    printf("%s\n", arr); //what it should be?

    nr = read(fd, arr, 8);

    printf("%d\n", (int)nr); //it should be 0
    printf("%s\n", arr); //what is the buffer looks like?
    return 0;

}
