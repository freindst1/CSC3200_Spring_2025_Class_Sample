#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>

int main(){
    FILE * file;
    file = fopen("genesis_line_reverse.txt", "r+");

    int ret;
    ret = fgetc(file);

    printf("%d\n", ret);
    
    ret = fgetc(file);

    printf("%d\n", ret);
    
    ret = fgetc(file);

    printf("%d\n", ret);

    fclose(file);

    return 0;
}