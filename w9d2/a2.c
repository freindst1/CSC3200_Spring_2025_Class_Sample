#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

//this is an examperiment to show if multiple processes can write to the same file at the same time
int main(){
    FILE * result;
    result = fopen("genesis_rebirth.txt", "w+"); //all processes share the same file as the output
    for(int i = 0; i < 5; i++){
        int pid = fork();
        if (pid == 0){
            printf("%d\n", pid);
            FILE * item;
            char filename[20];
            sprintf(filename, "genesis_part_%d.txt", i + 1);
            //filename = "genesis_part_1.txt";
            item = fopen(filename, "r");
            fseek(item, 0, SEEK_END);
            int size = ftell(item);
            char * buffer = malloc(size);
            printf("%d\n", size);
            rewind(item);
            fread(buffer, size, 1, item);
            fwrite(buffer, size, 1, result);
            free(buffer);
            fclose(item);
            //fflush(result);
            fclose(result);
            return 0;
        } else {
            sleep(1);
        }
    }
    //sleep(5);
    fclose(result);
    return 0;
}