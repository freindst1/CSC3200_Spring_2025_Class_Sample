#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>


int main(){
    int fd;
    fd = open("file.txt", O_RDONLY);

    int fd2;
    fd2 = creat("file_2.txt", 0644);

    char ch_buffer; //8 bites

    char arr[8];

    //what about &ch_buffer? 64bits
    ssize_t ret;
    while ((ret = read(fd, arr, 8 * sizeof(char))) > 0){
        //printf("%c", ch_buffer);
        write(fd2, arr, 8 * sizeof(char));
    }

    close(fd); 
    close(fd2);

    return 0;
}