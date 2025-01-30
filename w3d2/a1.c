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

    char arr[8];  //you do not need to worry about memory disposol

    char * buf;
    buf = malloc(8); //allocate 8 bytes starting from buf
    //any malloc memory, you have to manually release the memmory allocation
    

    //what about &ch_buffer? 64bits
    ssize_t ret;
    while ((ret = read(fd, buf, 8 * sizeof(char))) > 0){
        //printf("%c", ch_buffer);
        write(fd2, buf, ret);
    }
    //txt 12345678 | 9
    //ret 8        | 1

    close(fd); 
    close(fd2);
    free(buf);
    return 0;
}