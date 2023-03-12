#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// A utility function to get maximum value in arr[]
int getMax(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

// A function to do counting sort of arr[] according to the digit represented by exp.
void countSort(int arr[], int n, int exp) {
    int output[n];
    int count[10] = {0};

    // Store count of occurrences in count[]
    for (int i = 0; i < n; i++) {
        count[(arr[i] / exp) % 10]++;
    }

    // Change count[i] so that count[i] now contains actual position of this digit in output[]
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    // Build the output array
    for (int i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    // Copy the output array to arr[], so that arr[] now contains sorted numbers according to current digit
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }
}

// The main function to implement radix sort
void radixSort(int arr[], int n) {
    // Find the maximum number to know number of digits
    int max = getMax(arr, n);

    // Do counting sort for every digit from least significant digit to most significant digit
    for (int exp = 1; max / exp > 0; exp *= 10) {
        countSort(arr, n, exp);
    }
}

int main() {
    int n = 100000;
    int arr[n];
    srand(time(NULL));

    // Populate the array with random integers
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1000000;
    }

    // Measure the execution time
    clock_t t1 = clock();
    radixSort(arr, n);
    clock_t t2 = clock();
    double elapsed_time = ((double) (t2 - t1)) / CLOCKS_PER_SEC;

    //printf("Sorted array: ");
    for (int i = 0; i < n; i++) {
        //printf("%d ", arr[i]);
    }

    printf("\nElapsed time: %lf seconds\n", elapsed_time);

    return 0;
}
