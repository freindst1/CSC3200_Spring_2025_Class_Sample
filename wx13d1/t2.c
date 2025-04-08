#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define SIZE 20
int a[SIZE];

int rand_in_range(int min, int max) {
    return rand() % (max - min + 1) + min;
}

void shuffle(int * array, int length){
    for(int i = 0; i < length / 2 + 1; i ++){
        int r = rand_in_range(0, length - 1);
        int t = array[i];
        array[i] = array[r];
        array[r] = t;
    }
}

void display(int * array, int length){
    for(int i = 0; i < length; i ++){
        printf("%d -> ", array[i]);
    }
    printf(" **END**\n");
}

void merge(int low, int mid, int high){
    printf("merge from %d, %d, %d\n", low, mid, high);
    int leftSize = mid - low + 1;
    int rightSize = high - mid;
    int * leftArr = malloc(sizeof(int) * leftSize);
    int * rightArr = malloc(sizeof(int) * rightSize);
    for(int i = 0; i < leftSize; i++){
        leftArr[i] = a[low + i];
    }
    for(int i = 0; i < rightSize; i++){
        rightArr[i] = a[mid + i + 1];
    }

    int l = 0;
    int r = 0;
    int k = low;

    while(l < leftSize && r < rightSize){
        if (leftArr[l] < rightArr[r]){
            a[k] = leftArr[l];
            l++;
        } else {
            a[k] = rightArr[r];
            r++;
        }
        k++;
    }

    while (l < leftSize){
        a[k] = leftArr[l];
        l++;
        k++;
    }

    while (r < rightSize){
        a[k] = rightArr[r];
        r++;
        k++;
    }
    free(leftArr);
    free(rightArr);
}

void merge_sort(int low, int high){
    int mid = low + (high - low) / 2;
    if (low < high){
        merge_sort(low, mid);
        merge_sort(mid + 1, high);

        merge(low, mid, high);
    }
}

int main(){
    srand(time(NULL));

    for(int i = 0; i < SIZE; i++){
        a[i] = i + 1;
    }
    shuffle(a, SIZE);

    display(a, SIZE);

    merge_sort(0, SIZE - 1);

    display(a, SIZE);

    return 0;
}

