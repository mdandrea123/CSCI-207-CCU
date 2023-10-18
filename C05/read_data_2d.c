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
    printf("Usage: %s <in file> \n", argv[0]);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        usage(argv); // Display usage information if the number of command-line arguments is not 2.
        exit(1);
    }

    dtype **matrix;        // Declare a pointer to a 2D array of dtype.
    int rows = 0;          // Initialize the number of rows.
    int cols = 0;          // Initialize the number of columns.
    char *fname = argv[1]; // Store the second command-line argument as the input file name.
    double start;
    double end;
    double elapsed;

    GET_TIME(start); // Start measuring the execution time.

    // Initialize the 2D array from the file, print its contents, and then free the memory.
    initialize_from_file(&matrix, &rows, &cols, fname);
    print(matrix, rows, cols);
    free2d(&matrix);

    GET_TIME(end); // Stop measuring the execution time.
    elapsed = end - start;
    printf("The program took %e seconds\n", elapsed); // Print the elapsed time.

    return 0;
}
