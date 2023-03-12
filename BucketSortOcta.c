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

// Function to sort a part of the array
void* Sort_Part(void* arg)
{
    long int* arr = (long int*)arg;
    Bucket_Sort(arr, ARRAY_SIZE / 8);
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

    pthread_t threads[8];

    clock_t start_time = clock();

    // Creating threads and sorting each part of the array in a separate thread
    for (int i = 0; i < 8; i++) {
        pthread_create(&threads[i], NULL, Sort_Part, arr + i * (ARRAY_SIZE / 8));
    }

    // Waiting for the threads to finish
    for (int i = 0; i < 8; i++) {
        pthread_join(threads[i], NULL);
    }

    // Merging the eight sorted parts of the array
    Bucket_Sort(arr, ARRAY_SIZE);

    clock_t end_time = clock();

    printf("\nExecution time: %f seconds\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);

    return 0;
}
//
// Created by Shreyas Maitreya on 3/10/23.
//
