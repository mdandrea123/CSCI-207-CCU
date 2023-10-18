// Author: Michael Dandrea
// Class: CSCI 207
// Date: 10/2/2023
#include <stdio.h>
#include <stdlib.h>
#include "utilities.h"
#include "timer.h"

// Function to display the usage information for the program.
void usage(char **argv)
{
    printf("Usage: %s <num rows> <num cols> <min> <max> <outfile> \n", argv[0]);
}

int main(int argc, char *argv[])
{
    if (argc != 6)
    {
        usage(argv); // Display usage information if the number of command-line arguments is not 6.
        exit(1);
    }

    dtype **matrix = NULL;    // Declare a pointer to a 2D array of dtype.
    int rows = atoi(argv[1]); // Convert the first command-line argument to the number of rows.
    int cols = atoi(argv[2]); // Convert the second command-line argument to the number of columns.
    int min = atoi(argv[3]);  // Convert the third command-line argument to the minimum value.
    int max = atoi(argv[4]);  // Convert the fourth command-line argument to the maximum value.
    char *fname = argv[5];    // Store the fifth command-line argument as the output file name.

    srand(0); // Seed the random number generator.

    double start, end, elapsed;
    GET_TIME(start); // Start measuring the execution time.

    // Allocate memory for a 2D array, initialize it with random values, write it to a file, and then free the memory.
    allocate2d(&matrix, rows, cols);
    initialize(matrix, rows, cols, min, max);
    write_to_file(matrix, rows, cols, fname);
    free2d(&matrix);

    GET_TIME(end); // Stop measuring the execution time.
    elapsed = end - start;
    printf("This program took %e seconds\n", elapsed); // Print the elapsed time.

    return 0;
}
