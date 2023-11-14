#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>




void triABulles (int *T, int n) {
    int i,permute=1, temp;

    while (permute)
    {
        permute = 0;
        for (i = 0; i < n - 1; i++)
        {
            if (T[i] > T[i + 1])
            {
                temp = T[i];
                T[i] = T[i + 1];
                T[i + 1] = temp;
                permute = 1;
            }
        }
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

int main(int argc, char *argv[])
{

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

    // Sort and measure time for the ordered table
    start_time = clock();
    // triParInsertion(ordered, n);
    triABulles(ordered, n);
    end_time = clock();
    double elapsed_time_ordered = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Ordered Table (Sorted): ");
    printf("\n");
    printf("Time of execution (Ordered): %f seconds\n", elapsed_time_ordered);
    free(ordered);

    // Sort and measure time for the randomly shuffled table
    start_time = clock();
    // triParInsertion(random, n);
    triABulles(random, n);
    end_time = clock();
    double elapsed_time_random = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Randomly Shuffled Table (Sorted): ");
    printf("\n");
    printf("Time of execution (Random): %f seconds\n", elapsed_time_random);
    free(random);

    // Sort and measure time for the inverted table
    start_time = clock();
    // triParInsertion(inverted, n);
    triABulles(inverted, n);
    end_time = clock();
    double elapsed_time_inverted = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Inverted Table (Sorted): ");
    printf("\n");
    printf("Time of execution (Inverted): %f seconds\n", elapsed_time_inverted);
    free(inverted);

    return 0;
}
