// Author: Michael Dandrea
// Class: CSCI 207
// Date: 10/16/2023
#include <stdio.h>
#include <stdlib.h>
#include "utilities.h"
#include "timer.h"

// Function to display usage information for the program
void usage(char **argv)
{
    printf("Usage: %s <in file> <out filename>", argv[0]);
}

int main(int argc, char **argv)
{
    // Check if the correct number of command line arguments are provided
    if (argc != 3)
    {
        usage(argv);
        exit(1); // Exit the program with an error code
    }

    // Store the input file name and output file name in variables
    char *infile = argv[1];
    char *outfile = argv[2];

    // Declare variables for matrices and their dimensions
    dtype **m1 = NULL;
    dtype **m2 = NULL;
    dtype **m3 = NULL;
    int rows = 0;
    int cols = 0;

    // Variables for measuring execution time
    double start, end, elapsed;

    // Record the start time
    GET_TIME(start);

    // Initialize a matrix from the input file
    initialize_from_file(&m1, &rows, &cols, infile);

    // Allocate memory for two additional matrices with extra rows and columns
    allocate2d(&m2, rows, cols + 1);
    allocate2d(&m3, rows + 1, cols + 1);

    // Calculate matrix checksums and store them in the third matrix
    matrix_checksum(m1, m2, m3, rows, cols);

    // Write the third matrix to an output file
    write_to_file(m3, rows + 1, cols + 1, outfile);

    // Free allocated memory for matrices
    free2d(&m1);
    free2d(&m2);
    free2d(&m3);

    // Record the end time
    GET_TIME(end);

    // Calculate and display the elapsed time
    elapsed = end - start;
    printf("The program took %e seconds.\n", elapsed);

    return 0;
}
