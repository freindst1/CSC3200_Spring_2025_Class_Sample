#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>

int main(){

    FILE * fp;
    
    fp = fopen("file.txt", "r+");

    
    int ret;
    /*
    while ((ret = fgetc(fp)) != EOF){
        printf("%c", ret);
    }
    printf("\n");
    rewind(fp);
    */

    /*
    char * buf;
    buf = malloc(1000);

    char * s_ret;

    char str_arr[9999];

    while ((s_ret = fgets(buf, 10, fp)) != NULL){
        printf("%s", buf);
    }
    free(buf);
    */

    void * buf;
    buf = malloc(100);
    
    size_t s_ret;
    
    while ((s_ret = fread(buf, 3, 33, fp)) > 0){ //it will fail if the remain bits are not enough for a unit of block
        printf("%d\n", (int)s_ret);
    }

    fclose(fp);
    return 0;

}