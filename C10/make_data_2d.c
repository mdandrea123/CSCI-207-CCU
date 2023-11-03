// Author: Michael Dandrea
// Class: CSCI 207
// Date: 10/2/2023
// Updated: 10/17/2023
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "utilities.h"
#include "timer.h"

int main(int argc, char *argv[])
{
    int rows = 0, cols = 0, min = 0, max = 0;
    char *fname = NULL;
    int pFlag = 0; // Initialize the print flag to 0 (off).

    parseMake(argc, argv, &rows, &cols, &min, &max, &fname, &pFlag);

    if(fname == NULL)
    {
        printf(" Usage: [-r <#rows>] [-c <#cols>] [-l <low>] [-h <high>] -o <output filename> [-p]\n");
        exit(1);
    }

    dtype **matrix = NULL;

    srand(time(NULL)); // Seed the random number generator.

    double start, end, elapsed;
    GET_TIME(start); // Start measuring the execution time.

    // Allocate memory for a 2D array, initialize it with random values, write it to a file, and then free the memory.
    allocate2d(&matrix, rows, cols);
    initialize(matrix, rows, cols, min, max);
    write_to_file(matrix, rows, cols, fname);

     if (pFlag)
    {
        printf("Matrix:\n");
        print(matrix, rows, cols);
    }
    free2d(&matrix);
    GET_TIME(end); // Stop measuring the execution time.
    elapsed = end - start;
    printf("This program took %e seconds\n", elapsed); // Print the elapsed time.

   

    return 0;
}
