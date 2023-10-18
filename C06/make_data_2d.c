// Author: Michael Dandrea
// Class: CSCI 207
// Date: 10/2/2023
// Updated: 10/17/2023
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "utilities.h"
#include "timer.h"

// Function to display the usage information for the program.
void usage(char **argv)
{
    printf("Usage: %s -r <#rows> -c <#cols> -l <low> -h <high> -o <output filename> [-p]\n", argv[0]);
}

// Function to parse command-line arguments and update values through pointers.
void parse(int argc, char *argv[], int *rows, int *cols, int *min, int *max, char **fname, int *printFlag)
{
    *rows = 3; // Default value for rows.
    *cols = 4; // Default value for cols.
    *min = 0;  // Default value for min.
    *max = 9; // Default value for max.

    int opt;
    while ((opt = getopt(argc, argv, "r:c:l:h:o:p")) != -1)
    {
        switch (opt)
        {
        case 'r':
            *rows = atoi(optarg);
            break;
        case 'c':
            *cols = atoi(optarg);
            break;
        case 'l':
            *min = atoi(optarg);
            break;
        case 'h':
            *max = atoi(optarg);
            break;
        case 'o':
            *fname = optarg;
            break;
        case 'p':
            *printFlag = 1; // Set the print flag to 1 if the '-p' option is provided.
            break;
        default:
            usage(argv);
            exit(1);
        }
    }
}

int main(int argc, char *argv[])
{
    int rows = 0, cols = 0, min = 0, max = 0;
    char *fname = NULL;
    int pFlag = 0; // Initialize the print flag to 0 (off).

    parse(argc, argv, &rows, &cols, &min, &max, &fname, &pFlag);

    if (fname == NULL)
    {
        usage(argv);
        exit(1);
    }

    dtype **matrix = NULL;

    srand(0); // Seed the random number generator.

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
