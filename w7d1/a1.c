#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>

struct Pixel {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
};

int main(){
    FILE *origin, *new;

    origin = fopen("darthvador.bmp", "r");

    new = fopen("darthvador_90.bmp", "wb");

    //deal with header
    char * buffer;
    buffer = malloc(18);

    //firt 18 bytes remains the same
    fread(buffer, 18, 1, origin);
    fwrite(buffer, 18, 1, new);
    
    unsigned int width;
    fread(&width, 4, 1, origin);

    printf("%d\n", width);

    unsigned int height;
    fread(&height, 4, 1, origin);

    printf("%d\n", height);

    //write the new height and width into the new rotated picture
    unsigned int new_width = height;
    unsigned int new_height = width;
    fwrite(&height, 4, 1, new);
    fwrite(&width, 4, 1, new);

    //the rest 28 bytes are the same as well
    int size = 28;
    free(buffer);
    buffer = malloc(size);

    //done write header
    fread(buffer, size, 1, origin);
    fwrite(buffer, size, 1, new);
    free(buffer);
    
    //create a 2-d pixel array for the bitmap
    //struct Pixel maps[900][1440];
    
    unsigned char p_buf[3];

    unsigned char * map;
    map = malloc(3 * height * width);
    
    unsigned int * checker;
    checker = malloc(3 * height * width * sizeof(int));

    for(int i = 0; i < 3 * height * width; i++){
        checker[i] = 0;
    }

    int count = 3 * new_height * new_width;
    
    //scan all the pixels on the original file stream
    for(int y = 0; y < height; y++){
        for(int x = 0; x < width; x++){
            int ret;
            if ((ret = fread(p_buf, 3, 1, origin)) > 0){
                //p_buf holds one pixel data on the position (x, y) for each iteration of the loop
                //we transform the origin bitmap rotating 90 degrees here
                //p_buf at (x, y) - > pos = 54 + (new_width - y - 1) + x * new_height
                int pos = 3 * ((new_width - y - 1) + (x * new_width));
                //int pos = 3 * ((x))
                for(int n = 0; n < 3; n++){
                    map[pos + n] = p_buf[n];
                    checker[pos + n] = pos + n;
                }
                if (pos == 3){
                    printf("%d-%d-%d", p_buf[0], p_buf[1], p_buf[2]);
                }
                //fseek(new, pos, SEEK_SET);
                //fwrite(p_buf, 3, 1, new);
            } else {
                printf("read error\n");
            }
        }
    }


    fseek(new, 54, SEEK_SET);
    fwrite(map, 3 * new_height * new_width, 1, new);
    fseek(new, 54, SEEK_SET);
    fread(p_buf, 3, 1, new);
    free(map);

    fclose(origin);
    fclose(new);

    return 0;
}