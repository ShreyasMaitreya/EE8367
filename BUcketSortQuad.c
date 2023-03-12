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
void* Sort_Array(void* arg)
{
    long int* arr = (long int*)arg;
    Bucket_Sort(arr, ARRAY_SIZE / 4);
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

    pthread_t thread1, thread2, thread3, thread4;

    clock_t start_time = clock();

    // Creating threads and sorting 1/4th of the array in each thread
    pthread_create(&thread1, NULL, Sort_Array, arr);
    pthread_create(&thread2, NULL, Sort_Array, arr + ARRAY_SIZE / 4);
    pthread_create(&thread3, NULL, Sort_Array, arr + ARRAY_SIZE / 2);
    pthread_create(&thread4, NULL, Sort_Array, arr + 3 * ARRAY_SIZE / 4);

    // Waiting for the threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
    pthread_join(thread4, NULL);

    // Merging the sorted parts of the array
    Bucket_Sort(arr, ARRAY_SIZE);

    clock_t end_time = clock();

    printf("\nExecution time: %f seconds\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);

    return 0;
}
//
// Created by Shreyas Maitreya on 3/10/23.
//
