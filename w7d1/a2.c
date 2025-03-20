#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>

int main(){
    int width = 3; 
    int height = 4;
    int new_width = height;
    int new_height = width;
    int a[12];
    int b[12];
    for(int i = 0; i < 12; i++){
        a[i] = i;
    }
    int counter = 0;
    for (int y = 0; y < height; y++){
        for(int x = 0; x < width; x++){
            int pos = ((height - y - 1) + (x * new_width));
            b[pos] = counter;
            counter++;
            printf("(%d, %d) -> (%d, %d)\n", x, y, (height - y - 1), x);
        }
    }

    counter = 0;
    for(int y = 0; y < new_height; y++){
        for(int x = 0; x < new_width; x++){
            if (x == 0){
                printf("\n");
            }
            printf("%d ", b[counter]);
            counter++;
        }
    }

    return 0;
}