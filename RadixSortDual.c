#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define NUM_THREADS 2

int getMax(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

struct countSort_args {
    int *arr;
    int n;
    int exp;
};

void *countSort(void *arguments) {
    struct countSort_args *args = arguments;
    int *arr = args->arr;
    int n = args->n;
    int exp = args->exp;

    int output[n];
    int count[10] = {0};
    for (int i = 0; i < n; i++) {
        count[(arr[i] / exp) % 10]++;
    }
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }
    for (int i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }

    pthread_exit(NULL);
}

void radixSort(int arr[], int n) {
    int max = getMax(arr, n);

    pthread_t threads[NUM_THREADS];
    struct countSort_args args[NUM_THREADS];

    for (int exp = 1; max / exp > 0; exp *= 10) {
        int chunk_size = n / NUM_THREADS;
        for (int i = 0; i < NUM_THREADS; i++) {
            int start = i * chunk_size;
            int end = (i == NUM_THREADS - 1) ? n : start + chunk_size;

            args[i].arr = arr + start;
            args[i].n = end - start;
            args[i].exp = exp;

            pthread_create(&threads[i], NULL, countSort, &args[i]);
        }

        for (int i = 0; i < NUM_THREADS; i++) {
            pthread_join(threads[i], NULL);
        }
    }
}

int main() {
    int n = 100000;
    int arr[n];
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1000000;
    }
    clock_t t1 = clock();
    radixSort(arr, n);
    clock_t t2 = clock();
    double elapsed_time = ((double) (t2 - t1)) / CLOCKS_PER_SEC;
    printf("\nElapsed time: %lf seconds\n", elapsed_time);
    return 0;
}
//
// Created by Shreyas Maitreya on 3/7/23.
//
