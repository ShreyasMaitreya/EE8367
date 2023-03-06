#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define SIZE 1000000
#define THREADS 2

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i+1], &arr[high]);
    return i+1;
}

void quicksort_parallel(int arr[], int low, int high);

struct thread_data {
    int* arr;
    int low;
    int high;
};

void* quicksort_thread(void* arg) {
    struct thread_data* data = (struct thread_data*) arg;
    quicksort_parallel(data->arr, data->low, data->high);
    return NULL;
}

void quicksort_parallel(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        if (high - low < SIZE/THREADS) {
            quicksort_parallel(arr, low, pi - 1);
            quicksort_parallel(arr, pi + 1, high);
        }
        else {
            pthread_t threads[2];
            struct thread_data data[2];

            int mid = (low + high) / 2;

            data[0].arr = arr;
            data[0].low = low;
            data[0].high = mid;

            data[1].arr = arr;
            data[1].low = mid + 1;
            data[1].high = high;

            for (int i = 0; i < THREADS; i++) {
                pthread_create(&threads[i], NULL, quicksort_thread, (void*) &data[i]);
            }

            for (int i = 0; i < THREADS; i++) {
                pthread_join(threads[i], NULL);
            }
        }
    }
}

double get_execution_time(clock_t start_time, clock_t end_time) {
    return ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
}

int main() {
    int arr[SIZE];
    srand(time(NULL));

    // populate array with random integers
    for (int i = 0; i < SIZE; i++) {
        arr[i] = rand() % 1000;
    }

    clock_t start_time = clock();

    quicksort_parallel(arr, 0, SIZE - 1);

    clock_t end_time = clock();
    double execution_time = get_execution_time(start_time, end_time);

    printf("Sorted array:\n");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", arr[i]);
    }
    printf("\nExecution time: %f seconds\n", execution_time);

    return 0;
}
