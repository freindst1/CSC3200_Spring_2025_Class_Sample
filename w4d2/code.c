#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>

int main(){
    //find out how many bytes are there in the file
    //plan 1: read, add the successful read return together until read returns 0
    //plan 2: lseek. lseek returns the successful offset moved
    int genesis_fd;
    genesis_fd = open("genesis.txt", O_RDONLY);

    int offset;
    lseek(genesis_fd, 0, SEEK_SET); //force the offset to be 0
    offset = lseek(genesis_fd, 0, SEEK_END);    //move the offset to then end

    int half_1;
    half_1 = offset / 2;    //how many bytes for the genesis_1.txt
    int half_2;
    half_2 = offset - half_1;   //how many bytes for the genesis_2.txt

    char * buf;
    buf = malloc(1000);
    
    //write half_1 bytes into genesis_1.txt
    int fd;
    fd = creat("genesis_1.txt", 0644);

    lseek(genesis_fd, 0, SEEK_SET);
    while (half_1 > 0){
        int length;
        if (half_1 > 1000){
            length = 1000;
        } else if (half_1 > 0) {
            length = half_1;   
        }
        read(genesis_fd, buf, length); //return -1 when failed. otherwise return number of bytes read successfully
        half_1 = half_1 - length;
        write(fd, buf, length);
    }
    close(fd);

    fd = creat("genesis_2.txt", 0644);
        while (half_2 > 0){
        int length;
        if (half_2 > 1000){
            length = 1000;
        } else if (half_2 > 0) {
            length = half_2;   
        }
        read(genesis_fd, buf, length); //return -1 when failed. otherwise return number of bytes read successfully
        half_2 = half_2 - length;
        write(fd, buf, length);
    }
    close(fd);

    close(genesis_fd);

    free(buf);

    return 0;
}