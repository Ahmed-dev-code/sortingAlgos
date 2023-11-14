# Sorting Algorithms in C

This repository contains implementations of various sorting algorithms in the C programming language. The purpose is to compare the performance of these algorithms on different types of input data (sorted, random, reversed).

## List of Sorting Algorithms

1. [Insertion Sort](insertionTri.c)
2. [Bubble Sort](bubbleSort.c)
3. [Merge Sort](mergeSort.c)
4. [Quick Sort](quickSort.c)
5. [Heap Sort](heapSort.c)

## How to Use

1. Download the C file for the sorting algorithm you want to test.

2. Compile the C file using a C compiler. For example, using GCC:

    ```bash
    gcc -o bubble_sort bubble_sort.c
    ```

3. Execute the compiled program, specifying the number of elements you want to sort (`n`):

    ```bash
    ./bubble_sort n
    ```

4. The program will generate and sort arrays of size `n` for three scenarios: sorted, random, and reversed. It will then display the time taken for each scenario.

## Example

```bash
./bubble_sort 10000

