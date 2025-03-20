#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>

int main(){
    int c = 0;
    int width = 4;
    int height = 3;
    int new_width = width;
    int new_height = height;
    int arr[12];
    for(int y = 0; y < height; y++){
        for(int x = 0; x < width; x++){
            if (x == 0){
                printf("\n");
            }
            printf("%d ", c);
            //c is the index of the original 2-d array
            //the pixel at the position (x, y) is the c-th element in the original array
            //when rotating 90 degress the pixel should be at the position (new_width - y - 1, x)
            //int pos = (new_width - y - 1) + x * new_width;
            //when rotating 270 degress
            //(x, y ) -> (y, new_height - x - 1)
            //int pos = y + (new_height - x - 1) * new_width;
            //180 degrees: (x, y) -> (new_width - x - 1, new_height - y - 1)
            int pos = (new_width - x - 1) + (new_height - y - 1) * new_width;
            arr[pos] =  c;
            c++;
            //printf("(%d, %d) -> (%d, %d)\n", x, y, (new_width - y - 1), x);
        }
    }

    printf("\n");

    int index = 0;
    for(int y = 0; y < new_height; y++){
        for(int x = 0; x < new_width; x++){
            printf("%d ", arr[index]);
            index++;
            if (x == (new_width - 1)){
                printf("\n");
            }
        }
    }
    return 0;
}