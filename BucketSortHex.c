#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <pthread.h>

#define ARRAY_SIZE 100000
#define BUCKET_SIZE 100

// Function to find maximum element of the array
long int max_element(long int array[], long int size)
{
    long int max = LONG_MIN;
    for (long int i = 0; i < size; i++)
    {
        if (array[i] > max)
            max = array[i];
    }
    return max;
}

//Implementing bucket sort
void Bucket_Sort(long int array[], long int size)
{
    long int max = max_element(array, size);

    long int bucket[max+1];

    for (long int i = 0; i <= max; i++)
        bucket[i] = 0;

    for (long int i = 0; i < size; i++)
        bucket[array[i]]++;

    long int j=0;
    for (long int i = 0; i <= max; i++)
    {
        while (bucket[i] > 0)
        {
            array[j++] = i;
            bucket[i]--;
        }
    }
}

// Function to sort one part of the array
void* Sort_Array(void* arg)
{
    long int* arr = (long int*)arg;
    Bucket_Sort(arr, ARRAY_SIZE / 6);
    return NULL;
}

/* The main() begins */
int main()
{
    long int i;
    long int arr[ARRAY_SIZE];

    srand(time(NULL));
    for (i = 0; i < ARRAY_SIZE; i++) {
        arr[i] = rand() % BUCKET_SIZE;
    }

    pthread_t threads[6];

    clock_t start_time = clock();

    // Creating threads and sorting one part of the array in each thread
    for (int i = 0; i < 6; i++) {
        pthread_create(&threads[i], NULL, Sort_Array, arr + i * (ARRAY_SIZE / 6));
    }

    // Waiting for the threads to finish
    for (int i = 0; i < 6; i++) {
        pthread_join(threads[i], NULL);
    }

    // Merging the sorted parts of the array
    long int temp_arr[ARRAY_SIZE];
    long int block_size = ARRAY_SIZE / 6;
    long int block_starts[6] = {0, block_size, block_size*2, block_size*3, block_size*4, block_size*5};
    for (int i = 0; i < 6; i++) {
        for (int j = block_starts[i], k = 0; j < block_starts[i] + block_size && k < block_size; j++, k++) {
            temp_arr[j] = arr[i*block_size + k];
        }
    }
    Bucket_Sort(temp_arr, ARRAY_SIZE);

    clock_t end_time = clock();

    printf("\nExecution time: %f seconds\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);

    return 0;
}
//
// Created by Shreyas Maitreya on 3/10/23.
//
