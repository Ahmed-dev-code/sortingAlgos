#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void fusion(int tab1[], int n1, int tab2[], int n2, int T[]) {
    int i = 0, j = 0, k = 0;

    while (i < n1 && j < n2) {
        if (tab1[i] <= tab2[j]) {
            T[k] = tab1[i];
            i++;
        } else {
            T[k] = tab2[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        T[k] = tab1[i];
        i++;
        k++;
    }

    while (j < n2) {
        T[k] = tab2[j];
        j++;
        k++;
    }
}

void triFusion(int T[], int n) {
    if (n > 1) {
        int n1 = n / 2;
        int n2 = n - n1;

        // Reuse T for tab1 and tab2
        int *tab1 = T;
        int *tab2 = T + n1;

        triFusion(tab1, n1);
        triFusion(tab2, n2);

        int *temp = (int *)malloc(n * sizeof(int));
        // Check if malloc was successful, handle error if not

        fusion(tab1, n1, tab2, n2, temp);

        // Copy the merged result back to T
        int i;
        for (i = 0; i < n; i++) {
            T[i] = temp[i];
        }

        free(temp);
    }
}

void generateRandomTable(int n, int **table) {
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

void generateTable(int n, int **table) {
    *table = (int *)malloc(n * sizeof(int));
    int i;
    for (i = 0; i < n; i++) {
        (*table)[i] = i + 1;
    }
}

void generateInverseTable(int n, int **table) {
    *table = (int *)malloc(n * sizeof(int));
    int i;
    for (i = 0; i < n; i++) {
        (*table)[i] = n - i;
    }
}

void printTable(int T[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        printf("%d ", T[i]);
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <n>\n", argv[0]);
        return 1; // Exit with an error code
    }

    int n = atoi(argv[1]); // Convert the second command line argument to an integer
    printf("n: %d\n", n);

    int *table;

    clock_t start_time = clock();
    generateTable(n, &table);
    clock_t end_time = clock();
    double elapsed_time_generating = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("\n");
    printf("Time of execution (generating): %f seconds\n", elapsed_time_generating);

    // Sort and measure time for the table
    start_time = clock();
    triFusion(table, n);
    end_time = clock();
    double elapsed_time_ordered = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Table Ordered (Sorted): ");
    printf("\n");
    printf("Time of execution: %f seconds\n", elapsed_time_ordered);
    free(table);

    // Generate a random table and measure time for it
    start_time = clock();
    generateRandomTable(n, &table);
    end_time = clock();
    double elapsed_time_random = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    // Sort and measure time for the random table
    start_time = clock();
    triFusion(table, n);
    end_time = clock();
    double elapsed_time_random_ordered = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Table Random Ordered (Sorted): ");
    printf("\n");
    printf("Time of execution: %f seconds\n", elapsed_time_random_ordered);
    free(table);
    
    // Generate an inverse table and measure time for it
    start_time = clock();
    generateInverseTable(n, &table);
    end_time = clock();
    double elapsed_time_inverse = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    // Sort and measure time for the inverse table
    start_time = clock();
    triFusion(table, n);
    end_time = clock();
    double elapsed_time_inverse_ordered = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Table Inverse Ordered (Sorted): ");
    printf("\n");
    printf("Time of execution: %f seconds\n", elapsed_time_inverse_ordered);
    free(table);



    return 0;
}
