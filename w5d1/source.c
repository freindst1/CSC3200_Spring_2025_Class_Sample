#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>

int main(){
    FILE * file = fopen("file.txt", "r");

    if (file == NULL){
        printf("met file I/O error");
    } else {
        printf("%p", file);
    }

    printf("firt time %d\n", fclose(file));
    
    floseall();

    return 0;
}

/* with syntax inexplicitly close the stream, so programmer won't forget about it.
with(file = open("file.txt")){
    file.writeline("abc");
    //file.close();
}
*/