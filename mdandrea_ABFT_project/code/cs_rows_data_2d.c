// Author: Michael Dandrea
// Class: CSCI 207
// Date: 10/16/2023
// Updated: 10/18/2023
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "utilities.h"
#include "timer.h"

int main(int argc, char **argv)
{
    // Declare variables for matrices and their dimensions
    dtype **m1 = NULL;
    dtype **m2 = NULL;
    int rows = 0;
    int cols = 0;

    // Declare variables for input file name, output file name, and print flag
    char *infile = NULL;
    char *outfile = NULL;
    int pFlag = 0;

    // Variables for measuring execution time
    double start, end, elapsed;

    // Parse command line arguments and store the input file name, output file name, and print flag in variables
    parseRows(argc, argv, &infile, &outfile, &pFlag);

    if(infile == NULL || outfile == NULL)
    {
        printf("Usage: [-p] -i <in file> -o <out filename>\n");
        exit(1);
    }

    // Record the start time
    GET_TIME(start);

    // Initialize a matrix from the input file
    initialize_from_file(&m1, &rows, &cols, infile);

    // Allocate memory for another matrix with an extra column
    allocate2d(&m2, rows, cols + 1);

    // Calculate row checksums and store them in the second matrix
    row_checksum(m1, m2, rows, cols);

    // Write the second matrix to an output file
    write_to_file(m2, rows, cols + 1, outfile);

    // Print the matrices to the console if the print flag is set
    if (pFlag)
    {
        printf("Matrix 1:\n");
        print(m1, rows, cols);
        printf("Matrix 2:\n");
        print(m2, rows, cols + 1);
    }

    // Free allocated memory for matrices
    free2d(&m1);
    free2d(&m2);

    // Record the end time
    GET_TIME(end);

    // Calculate and display the elapsed time
    elapsed = end - start;
    printf("The program took %e seconds.\n", elapsed);

    return 0;
}
