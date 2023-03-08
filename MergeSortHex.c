#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define SIZE 100000
#define NUM_THREADS 6

void merge(long long int arr[], long long int left[], long long int left_size, long long int right[], long long int right_size) {
    long long int i = 0, j = 0, k = 0;

    while (i < left_size && j < right_size) {
        if (left[i] < right[j]) {
            arr[k] = left[i];
            i++;
        } else {
            arr[k] = right[j];
            j++;
        }
        k++;
    }

    while (i < left_size) {
        arr[k] = left[i];
        i++;
        k++;
    }

    while (j < right_size) {
        arr[k] = right[j];
        j++;
        k++;
    }
}

void merge_sort(long long int arr[], long long int size) {
    if (size < 2) {
        return;
    }

    long long int mid = size / 2;
    long long int* left = malloc(mid * sizeof(long long int));
    long long int* right = malloc((size - mid) * sizeof(long long int));

    for (long long int i = 0; i < mid; i++) {
        left[i] = arr[i];
    }

    for (long long int i = mid; i < size; i++) {
        right[i - mid] = arr[i];
    }

    merge_sort(left, mid);
    merge_sort(right, size - mid);

    merge(arr, left, mid, right, size - mid);

    free(left);
    free(right);
}

typedef struct {
    long long int* arr;
    long long int size;
} thread_data_t;

void* sort_thread(void* arg) {
    thread_data_t* data = (thread_data_t*) arg;
    merge_sort(data->arr, data->size);
    pthread_exit(NULL);
}

double get_execution_time(clock_t start_time, clock_t end_time) {
    return ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
}

int main() {
    long long int* arr = malloc(SIZE * sizeof(long long int));
    srand(time(NULL));

    // populate array with random integers
    for (long long int i = 0; i < SIZE; i++) {
        arr[i] = rand() % 1000;
    }

    clock_t start_time = clock();

    pthread_t threads[NUM_THREADS];
    thread_data_t thread_data[NUM_THREADS];
    long long int segment_size = SIZE / NUM_THREADS;

    for (int i = 0; i < NUM_THREADS; i++) {
        thread_data[i].arr = arr + i * segment_size;
        thread_data[i].size = segment_size;
        pthread_create(&threads[i], NULL, sort_thread, (void*) &thread_data[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // merge the sub-arrays in pairs
    for (int i = 1; i < NUM_THREADS; i *= 2) {
        for (int j = 0; j < NUM_THREADS - i; j += 2 * i) {
            merge(arr + j * segment_size, arr + j * segment_size, i * segment_size, arr + (j + i) * segment_size, i * segment_size);
        }
    }

    clock_t end_time = clock();
    double execution_time = get_execution_time(start_time, end_time);

    //printf("Sorted array:\n");
    for (long int i = 0; i < SIZE; i++) {
        //printf("%ld ", arr[i]);
    }
    printf("\nExecution time: %f seconds\n", execution_time);

    return 0;
}

