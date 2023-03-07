#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define SIZE 1000000
#define THREADS 4

void swap(long int* a, long int* b) {
    long int temp = *a;
    *a = *b;
    *b = temp;
}

long int partition(long int arr[], long int low, long int high) {
    long int pivot = arr[high];
    long int i = low - 1;

    for (long int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i+1], &arr[high]);
    return i+1;
}

void quicksort_parallel(long int arr[], long int low, long int high);

struct thread_data {
    long int* arr;
    long int low;
    long int high;
};

void* quicksort_thread(void* arg) {
    struct thread_data* data = (struct thread_data*) arg;
    quicksort_parallel(data->arr, data->low, data->high);
    return NULL;
}

void quicksort_parallel(long int arr[], long int low, long int high) {
    if (low < high) {
        long int pi = partition(arr, low, high);

        if (high - low < SIZE/THREADS) {
            quicksort_parallel(arr, low, pi - 1);
            quicksort_parallel(arr, pi + 1, high);
        }
        else {
            pthread_t threads[2];
            struct thread_data data[2];

            long int mid = (low + high) / 2;

            data[0].arr = arr;
            data[0].low = low;
            data[0].high = mid;

            data[1].arr = arr;
            data[1].low = mid + 1;
            data[1].high = high;

            for (long int i = 0; i < THREADS/2; i++) {
                pthread_create(&threads[i], NULL, quicksort_thread, (void*) &data[i]);
            }

            for (long int i = 0; i < THREADS/2; i++) {
                pthread_join(threads[i], NULL);
            }
        }
    }
}

double get_execution_time(clock_t start_time, clock_t end_time) {
    return ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
}

int main() {
    long int arr[SIZE];
    srand(time(NULL));

    // populate array with random integers
    for (long int i = 0; i < SIZE; i++) {
        arr[i] = rand() % 1000;
    }

    clock_t start_time = clock();

    quicksort_parallel(arr, 0, SIZE - 1);

    clock_t end_time = clock();
    double execution_time = get_execution_time(start_time, end_time);

    //printf("Sorted array:\n");
    for (long int i = 0; i < SIZE; i++) {
        //printf("%ld ", arr[i]);
    }
    printf("\nExecution time: %f seconds\n", execution_time);

    return 0;
}
