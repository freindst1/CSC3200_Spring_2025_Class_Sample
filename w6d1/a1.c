#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>

int main(){
    FILE * genesis, *genesis_reverse, *genesis_reverse_para;

    genesis = fopen("genesis.txt", "r");
    
    //this file holds every character in reverse position
    genesis_reverse = fopen("genesis_reverse.txt", "w+");

    //this file holds every character reveresely in each paragraph
    genesis_reverse_para = fopen("genesis_line_reverse.txt", "w+");

    fseek(genesis, 0, SEEK_END);

    int size = ftell(genesis);

    rewind(genesis);

    char * buf;

    buf = malloc(size);

    fread(buf, size, 1, genesis);   //read the genesis.txt into the buf char[]

    //reverse the char from buf to buf1

    char * buf1;
    buf1 = malloc(size);

    for(int i = 0; i < size; i++){
        buf1[i] = buf[size - 1 - i];
    }

    fwrite(buf1, size, 1, genesis_reverse);

    fflush(genesis_reverse);


    //1: read character by character from genesis to the buffer
    //2: when we see a line break, stop, and flip the charaters in the buffer
    //3: write the buffer into the file stream
    //4: go back read and repeat from step 1 to 3 until the end of the file

    rewind(genesis);

    int ret;

    char * buf2;
    buf2 = malloc(size);
    int count = 0;

    while((ret = fgetc(genesis)) != EOF){
        char c = (char)ret;
        if (c == '\r'){
            continue;
        }
        buf2[count] = c;
        count++;
        if (c == '\n'){
            //reverse everything in the buf2
            char * buf3;
            buf3 = malloc(count + 1);
            for(int i = 0; i < count; i++){
                buf3[i] = buf2[count - i - 1];
            }
            fwrite(buf3, count, 1, genesis_reverse_para);   //move one paragraph into new file
            free(buf3);
            count = 0;
        } 
    }

    if (count != 0){
        char * buf3;
        buf3 = malloc(count + 1);
        for(int i = 0; i < count; i++){
            buf3[i] = buf2[count - i - 1];
        }
        fwrite(buf3, count, 1, genesis_reverse_para);
        free(buf3);
    }

    free(buf2);
    free(buf);

    fclose(genesis);
    fclose(genesis_reverse);
    fclose(genesis_reverse_para);

    return 0;
}