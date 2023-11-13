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
        int i;
        int n1 = n / 2;
        int n2 = n - n1;

        int tab1[n1];
        int tab2[n2];

        // Initialiser et copier la première moitié du tableau dans tab1
        for (i = 0; i < n1; i++) {
            tab1[i] = T[i];
        }

        // Initialiser et copier la deuxième moitié du tableau dans tab2
        for (i = 0; i < n2; i++) {
            tab2[i] = T[i + n1];
        }

        // Appeler récursivement triFusion pour chaque moitié
        triFusion(tab1, n1);
        triFusion(tab2, n2);

        // Appeler la fonction de fusion
        fusion(tab1, n1, tab2, n2, T);
    }
}


void generateTable(int n, int **ordered, int **inverted, int **random)
{
    // Allocate memory for tables
    *ordered = (int *)malloc(n * sizeof(int));
    *inverted = (int *)malloc(n * sizeof(int));
    *random = (int *)malloc(n * sizeof(int));
    int i;
    // Generate ordered table
    for (i = 0; i < n; i++)
    {
        (*ordered)[i] = i + 1;
    }

    // Generate inverted table
    for (i = 0; i < n; i++)
    {
        (*inverted)[i] = n - i;
    }

    // Generate randomly shuffled table
    for (i = 0; i < n; i++)
    {
        (*random)[i] = i + 1;
    }

    // Shuffle the randomly shuffled table using the Fisher-Yates algorithm
    srand((unsigned int)time(NULL));
    for (i = n - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        // Swap
        int temp = (*random)[i];
        (*random)[i] = (*random)[j];
        (*random)[j] = temp;
    }
}

void printTable(int T[], int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        printf("%d ", T[i]);
    }
    printf("\n");
}




int main(int argc, char *argv[]) {
    if (argc != 2)
    {
        printf("Usage: %s <n>\n", argv[0]);
        return 1; // Exit with an error code
    }

    int n = atoi(argv[1]); // Convert the second command line argument to an integer
    printf("n: %d\n", n);

    int *ordered, *inverted, *random;

    clock_t start_time = clock();
    generateTable(n, &ordered, &inverted, &random);
    clock_t end_time = clock();
    double elapsed_time_generating = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("\n");
    printf("Time of execution (generating): %f seconds\n", elapsed_time_generating);

    // // print the table before sorting
    // printf("Ordered Table (Unsorted): ");
    // printTable(ordered, n);
    // printf("Randomly Shuffled Table (Unsorted): ");
    // printTable(random, n);
    // printf("Inverted Table (Unsorted): ");
    // printTable(inverted, n);

    

    // Sort and measure time for the ordered table
    start_time = clock();
    triFusion(ordered, n);
    end_time = clock();
    double elapsed_time_ordered = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Ordered Table (Sorted): ");
    printf("\n");
    printf("Time of execution (Ordered): %f seconds\n", elapsed_time_ordered);
    // free(ordered);

    // Sort and measure time for the randomly shuffled table
    start_time = clock();
    triFusion(random, n);
    end_time = clock();
    double elapsed_time_random = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Randomly Shuffled Table (Sorted): ");
    printf("\n");
    printf("Time of execution (Random): %f seconds\n", elapsed_time_random);
    // free(random);

    // Sort and measure time for the inverted table
    start_time = clock();
    triFusion(inverted, n);
    end_time = clock();
    double elapsed_time_inverted = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Inverted Table (Sorted): ");
    printf("\n");
    printf("Time of execution (Inverted): %f seconds\n", elapsed_time_inverted);
    // free(inverted);

    // Print the sorted tables
    // printf("Ordered Table (sorted): ");
    // printTable(ordered, n);
    // printf("Randomly Shuffled Table (sorted): ");
    // printTable(random, n);
    // printf("Inverted Table (sorted): ");
    // printTable(inverted, n);





    return 0;




}
