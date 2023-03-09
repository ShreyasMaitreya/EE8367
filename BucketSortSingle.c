#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 100000
#define BUCKET_SIZE 100

void bucketSort(long int arr[], long int n) {
    long int i, j;
    long int count[BUCKET_SIZE] = {0};
    long int *bucket = malloc(n * sizeof(long int));

    for (i = 0; i < n; i++) {
        count[arr[i]]++;
    }

    for (i = 1; i < BUCKET_SIZE; i++) {
        count[i] += count[i - 1];
    }

    for (i = n - 1; i >= 0; i--) {
        bucket[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }

    for (i = 0, j = 0; i < BUCKET_SIZE; i++) {
        while (count[i]-- > 0) {
            arr[j++] = bucket[i];
        }
    }

    free(bucket);
}

int main() {
    long int i;
    long int arr[ARRAY_SIZE];

    srand(time(NULL));
    for (i = 0; i < ARRAY_SIZE; i++) {
        arr[i] = rand() % BUCKET_SIZE;
    }

    clock_t start_time = clock();
    bucketSort(arr, ARRAY_SIZE);
    clock_t end_time = clock();

    printf("Sorted array:\n");
    for (i = 0; i < ARRAY_SIZE; i++) {
        printf("%ld ", arr[i]);
    }

    printf("\nExecution time: %f seconds\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);

    return 0;
}
