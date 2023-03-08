#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100000

void merge(long int arr[], long int left[], long int left_size, long int right[], long int right_size) {
    long int i = 0, j = 0, k = 0;

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

void merge_sort(long int arr[], long int size) {
    if (size < 2) {
        return;
    }

    long int mid = size / 2;
    long int left[mid];
    long int right[size - mid];

    for (long int i = 0; i < mid; i++) {
        left[i] = arr[i];
    }

    for (long int i = mid; i < size; i++) {
        right[i - mid] = arr[i];
    }

    merge_sort(left, mid);
    merge_sort(right, size - mid);

    merge(arr, left, mid, right, size - mid);
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

    merge_sort(arr, SIZE);

    clock_t end_time = clock();
    double execution_time = get_execution_time(start_time, end_time);

    //printf("Sorted array:\n");
    for (long int i = 0; i < SIZE; i++) {
        //printf("%ld ", arr[i]);
    }
    printf("\nExecution time: %f seconds\n", execution_time);

    return 0;
}
