#include <stdlib.h>
#include <stdio.h>

unsigned int bitsToInt(char * bits);

/* 
path is the original bmp image file path
newPath is the modified bmp image file path
mode is the rotation degree
mode = 0: simply duplicate the image, no change to header
mode = 1: rotate 90 degree clockwise, swap height with width
mode = 2: rotate 180 degree clockwise, no change to header
mode = 3: rotate 270 degree clockwise, swap height with width
*/
void rotate(char * path, char  * newPath, int mode);

int pixelRotation(int x, int y, int width, int height, int mode);

int main(){
    char * filePath = "darthvador.bmp";
    char * file1 = "90degree.bmp";
    char * file2 = "180degree.bmp";
    char * file3 = "270degree.bmp";
    char * file0 = "image_copy.bmp";
    rotate(filePath, file0, 0);
    rotate(filePath, file1, 1);
    rotate(filePath, file2, 2);
    rotate(filePath, file3, 3);

    return 0;
}


unsigned int bitsToInt(char * bits){ //argument is 8 bit * 4 array
    //bits = char[4]{'A', 'B', 'C', 'D'};
    return (unsigned char)bits[0] | ((unsigned char)bits[1] << 8) | ((unsigned char)bits[2] << 16) | ((unsigned char)bits[3] << 24);
}


void rotate(char * path, char  * newPath, int mode){
    FILE * inputStream, * outputStream;
    inputStream = fopen(path, "rb");
    outputStream = fopen(newPath, "wb");

    char intBuf[4];

    //read the width, height and size from header;
    int sizePos, heightPos, widthPos;
    sizePos = 2;
    heightPos = 22;
    widthPos = 18;
    unsigned int size, height, width;

    //move the file pointer to the pos
    fseek(inputStream, sizePos, SEEK_SET);
    //read 4 bytes out into buf;
    fread(intBuf, 4, 1, inputStream);
    size = bitsToInt(intBuf);

    fseek(inputStream, heightPos, SEEK_SET);
    fread(intBuf, 4, 1, inputStream);
    height = bitsToInt(intBuf);

    fseek(inputStream, widthPos, SEEK_SET);
    fread(intBuf, 4, 1, inputStream);
    width = bitsToInt(intBuf);

    char * readBuffer;
    char * writeBuffer;
    readBuffer = malloc(size);
    writeBuffer = malloc(size);

    fseek(inputStream, 0, SEEK_SET);
    fread(readBuffer, size, 1, inputStream);

    //complete the write to image header
    //for mode 0 and 2, we do not need to modifity it
    for(int i = 0; i < 54; i++){
        writeBuffer[i] = readBuffer[i];
    }

    //for mode 1 and 3, we need to swap the 4 bits start from widthPos 
    // and 4 bits start from heightPos
    //18 <-> 22, 19 <-> 23, 20 <-> 24, 21 <-> 25
    if (mode == 1 || mode == 3){
        for(int i = 0; i < 4; i++){
            writeBuffer[widthPos + i] = readBuffer[heightPos + i];
            writeBuffer[heightPos + i] = readBuffer[widthPos + i];
        }
    }

    for(int y = 0; y < height; y++){
        for (int x = 0; x < width; x++){
            int old_pixel = y * width + x;
            int new_pixel;
            new_pixel = pixelRotation(x, y, width, height, mode);
            for (int i = 0; i < 3; i++){
                int old_index, new_index;
                old_index = 54 + old_pixel * 3 + i;
                new_index = 54 + new_pixel * 3 + i;
                writeBuffer[new_index] = readBuffer[old_index];
            }
        }
    }

    fwrite(writeBuffer, size, 1, outputStream);

    fclose(inputStream);
    fclose(outputStream);

    free(readBuffer);
    free(writeBuffer);
}

int pixelRotation(int x, int y, int width, int height, int mode){
    switch (mode){
        case 1: //90 degrees
        return height - y - 1 + x * height;
        case 2: //180 degrees
        return (height - y - 1) * width + (width - x - 1);
        case 3: //270 degrees
        return y + (width - x -1) * height;
        default: //do notchange
        return y * width + x;
    }
}