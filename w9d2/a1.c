#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

int main(){
    FILE * genesis;
    genesis = fopen("genesis.txt", "r");
    fseek(genesis, 0, SEEK_END);
    long count = ftell(genesis);
    printf("%d\n", (int)count);
    int n = 5;
    int length = count / 5;
    fseek(genesis, 0, SEEK_SET);
    for(int i = 0; i < 5; i++){
        //the parent process main file stream never moved
        int pid = fork();
        if (pid == 0){
            char * buffer;
            buffer = malloc(length);
            fseek(genesis, i * length, SEEK_SET);
            fread(buffer, length, 1, genesis);
            char * filename;
            sprintf(filename, "genesis_part_%d.txt", i + 1);
            FILE * newfile;
            newfile = fopen(filename, "w+");
            fwrite(buffer, length, 1, newfile);
            fclose(newfile);
            free(buffer);
            sleep(i * 3);
            return 0;
        }
    }
    fclose(genesis);
    return 0;
}