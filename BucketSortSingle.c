/*
 * C Program to Implement Bucket Sort
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#define ARRAY_SIZE 100000
#define BUCKET_SIZE 100

//Function to find maximum element of the array
long int max_element(long int array[], long int size)
{
    // Initializing max variable to minimum value so that it can be updated
    // when we encounter any element which is greater than it.
    long int max = LONG_MIN;
    for (long int i = 0; i < size; i++)
    {
        //Updating max when array[i] is greater than max
        if (array[i] > max)
            max = array[i];
    }
    //return the max element
    return max;
}

//Implementing bucket sort
void Bucket_Sort(long int array[], long int size)
{
    //Finding max element of array which we will use to create buckets
    long int max = max_element(array, size);

    // Creating buckets
    long int bucket[max+1];

    //Initializing buckets to zero
    for (long int i = 0; i <= max; i++)
        bucket[i] = 0;

    // Pushing elements in their corresponding buckets
    for (long int i = 0; i < size; i++)
        bucket[array[i]]++;

    // Merging buckets effectively
    long int j=0;   // j is a variable which points at the index we are updating
    for (long int i = 0; i <= max; i++)
    {
        // Running while loop until there is an element in the bucket
        while (bucket[i] > 0)
        {
            // Updating array and increment j
            array[j++] = i;

            // Decreasing count of bucket element
            bucket[i]--;
        }
    }
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

    clock_t start_time = clock();
    Bucket_Sort(arr, ARRAY_SIZE);
    clock_t end_time = clock();

   // printf("Sorted array:\n");
    for (i = 0; i < ARRAY_SIZE; i++) {
        // printf("%ld ", arr[i]);
    }

    printf("\nExecution time: %f seconds\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);

    return 0;
}
