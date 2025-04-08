#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define SIZE 20
int a[SIZE];

struct range {
    int low;
    int high;
};

void display(){
    for(int i = 0; i < SIZE; i++){
        printf("%d -> ", a[i]);
    }
    printf("***END***\n");
}

int random_in_range(int min, int max){
    int remainder = rand() % (max - min + 1);
    return remainder + min;
}

//swap the number in each position to a random position
void shuffle(){
    for(int i = 0; i < SIZE; i++){
        int t = a[i];
        int r = random_in_range(0, 19);
        a[i] = a[r];
        a[r] = t;
    }
}

//merge the sorted left array and right array into a full-sorted array
//left array starts at index low, ends at index mid
//right array starts at index mid + 1, ends at index hgih
void merging(int low, int mid, int high){
    //create two temp array for left and right array
    int left_size = mid - low + 1;
    int right_size = high - mid;
    int *leftArray = malloc(left_size * sizeof(int));
    int *rightArray = malloc(right_size * sizeof(int));
    //copy elements from the original array to the left and right array
    for(int i = 0; i < left_size; i++){
        leftArray[i] = a[low + i];
    }
    for(int i = 0; i < right_size; i++){
        rightArray[i] = a[mid + i + 1];
    }
    //merging
    int l = 0;
    int r = 0;
    int k = low;
    while (l < left_size && r < right_size){
        if (leftArray[l] < rightArray[r]){
            a[k] = leftArray[l];
            l++;
        } else {
            a[k] = rightArray[r];
            r++;
        }
        k++;
    }

    while (l < left_size){
        a[k] = leftArray[l];
        k++;
        l++;
    }

    while (r < right_size){
        a[k] = rightArray[r];
        k++;
        r++;
    }
}

void merge_sort(int low, int high){
    if (low < high){
        int mid = low + (high - low) / 2;
        //create one thread for this
        merge_sort(low, mid);
        //creat another thread for this
        merge_sort(mid + 1, high);
        merging(low, mid, high);
    }
}

void * p_merge_sort(void *arg){
    struct range* r = (struct range*)arg;
    r->low;

}

int main(){
    for(int i = 0; i < SIZE; i++){
        a[i] = i;
    }
    srand(time(NULL));
    shuffle();
    display();
    merge_sort(0, SIZE - 1);
    display();
    return 0;
}