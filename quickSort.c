#include <stdio.h>
#include <stdlib.h>
#include <time.h>


// Function to swap two elements in an array
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to find the median of three elements
int medianOfThree(int arr[], int deb, int fin) {
    int mid = (deb + fin) / 2;

    // Comparisons to find the median
    if (arr[deb] > arr[mid]) {
        swap(&arr[deb], &arr[mid]);
    }

    if (arr[deb] > arr[fin]) {
        swap(&arr[deb], &arr[fin]);
    }

    if (arr[mid] > arr[fin]) {
        swap(&arr[mid], &arr[fin]);
    }

    return mid;
}

// Function for partitioning
int partition(int arr[], int deb, int fin) {
    int pivotIndex = medianOfThree(arr, deb, fin);
    int pivot = arr[pivotIndex];

    // Swap the pivot with the last element to temporarily place it at the end
    swap(&arr[pivotIndex], &arr[fin]);

    int i = deb - 1;
    int j;
    for ( j = deb; j < fin; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    // Put the pivot back to its correct position
    swap(&arr[i + 1], &arr[fin]);

    return i + 1;
}

// Recursive quicksort function
void quicksort(int arr[], int deb, int fin) {
    if (deb < fin) {
        int pivotIndex = partition(arr, deb, fin);

        // Recursive sorting of the two subarrays
        quicksort(arr, deb, pivotIndex - 1);
        quicksort(arr, pivotIndex + 1, fin);
    }
}

// Function to print an array
void printArray(int arr[], int size) {
    int i;
    for ( i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void generateInverseTable (int n, int **table) {
    *table = (int *)malloc(n * sizeof(int));
    int i;
    for (i = 0; i < n; i++) {
        (*table)[i] = n - i;
    }
}

void generateTable (int n, int **table) {
    *table = (int *)malloc(n * sizeof(int));
    int i;
    for (i = 0; i < n; i++) {
        (*table)[i] = i + 1;
    }
}

void generateRandomTable (int n, int **table) {
    *table = (int *)malloc(n * sizeof(int));
    int i;
    for (i = 0; i < n; i++) {
        (*table)[i] = i + 1;
    }

    // Shuffle the table using the Fisher-Yates algorithm
    srand((unsigned int)time(NULL));
    for (i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        // Swap
        int temp = (*table)[i];
        (*table)[i] = (*table)[j];
        (*table)[j] = temp;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: ./quickSort <size>\n");
        return 1;
    }

    int n = atoi(argv[1]);
    printf("n: %d\n", n);

    int *table;
    
    clock_t start_time = clock();
    generateTable(n, &table);
    clock_t end_time = clock();
    double elapsed_time_generating = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("\n");
    printf("Time of execution (generating): %f seconds\n", elapsed_time_generating);

    // Sort and measure time for the table
    // // print table before
    // printArray(table, n);
    start_time = clock();
    quicksort(table, 0, n - 1);
    end_time = clock();
    double elapsed_time_ordered = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Table Ordered (Sorted): ");
    printf("\n");
    printf("Time of execution: %f seconds\n", elapsed_time_ordered);
    // // print the table after 
    // printArray(table, n);
    free(table);

    // Generate a random table and measure time for it
    start_time = clock();
    generateRandomTable(n, &table);
    end_time = clock();
    double elapsed_time_random = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    // Sort and measure time for the random table
    // // print table before
    // printArray(table, n);
    start_time = clock();
    quicksort(table, 0, n - 1);
    end_time = clock();
    double elapsed_time_random_ordered = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Table Random Ordered (Sorted): ");
    printf("\n");
    printf("Time of execution: %f seconds\n", elapsed_time_random_ordered);
    // // print the table after 
    // printArray(table, n);
    free(table);
    
    // Generate an inverse table and measure time for it
    start_time = clock();
    generateInverseTable(n, &table);
    end_time = clock();
    double elapsed_time_inverse = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    // Sort and measure time for the inverse table
    // // print table before
    // printArray(table, n);

    start_time = clock();
    quicksort(table, 0, n - 1);
    end_time = clock();
    double elapsed_time_inverse_ordered = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Table Inverse Ordered (Sorted): ");
    printf("\n");
    printf("Time of execution: %f seconds\n", elapsed_time_inverse_ordered);
    // // print the table after 
    // printArray(table, n);
    free(table);



    return 0;

    
    
}
