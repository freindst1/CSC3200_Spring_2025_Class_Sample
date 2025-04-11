#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>

#define SIZE 100000
int a[SIZE];

//we manual decide that the maximu number of threads cannot exceed the cap
#define TCAP 100
int thread_total;   //global variable
pthread_mutex_t lock;

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
    if (r->low < r->high){
        if (thread_total >= TCAP){
            merge_sort(r->low, r->high);
        } else {
            int mid = r->low + (r->high - r->low) /2;
            pthread_t p1, p2;
            struct range r1;
            r1.low = r->low;
            r1.high = mid;
            pthread_create(&p1, NULL, p_merge_sort, &r1);
            pthread_mutex_lock(&lock);
            thread_total++;
            pthread_mutex_unlock(&lock);
            struct range r2;
            r2.low = mid + 1;
            r2.high = r->high;
            pthread_create(&p2, NULL, p_merge_sort, &r2);
            pthread_mutex_lock(&lock);
            thread_total++;
            pthread_mutex_unlock(&lock);
            pthread_join(p1, NULL);
            pthread_join(p2, NULL);
            merging(r->low, mid, r->high);
        }
    }
}

void merge_sort_p(int low, int high){
    struct range r;
    r.low = low;
    r.high = high;
    pthread_t p;
    pthread_create(&p, NULL, p_merge_sort, &r);
    pthread_mutex_lock(&lock);
    thread_total++;
    pthread_mutex_unlock(&lock);
    pthread_join(p, NULL);
}

int main(){
    pthread_mutex_init(&lock, NULL);
    for(int i = 0; i < SIZE; i++){
        a[i] = i;
    }
    struct timeval tv0;
    struct timeval tv1;

    srand(time(NULL));
    shuffle();
    //display();
    gettimeofday(&tv0, 0);
    //merge_sort(0, SIZE - 1);
    merge_sort_p(0, SIZE - 1);
    gettimeofday(&tv1, 0);
    //display();
    long elaps = (tv1.tv_usec-tv0.tv_usec);
    printf("%ld\n", tv0.tv_usec);
    printf("%ld\n", tv1.tv_usec);
    printf("%ld\n", tv0.tv_sec);
    printf("%ld\n", tv1.tv_sec);
    printf("the total time cost in merge sort is %ld ms\n", elaps);
    pthread_mutex_destroy(&lock);
    return 0;
}

