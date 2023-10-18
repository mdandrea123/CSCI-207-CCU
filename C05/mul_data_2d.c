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
    printf("Usage: %s <in file1> <in file2> <out filename>", argv[0]);
}

int main(int argc, char **argv)
{
    // Check if the correct number of command line arguments are provided
    if (argc != 4)
    {
        usage(argv);
        exit(1); // Exit the program with an error code
    }

    // Store the input file names and output file name in variables
    char *infile1 = argv[1];
    char *infile2 = argv[2];
    char *outfile = argv[3];

    // Declare variables for matrices and their dimensions
    dtype **m1 = NULL;
    dtype **m2 = NULL;
    dtype **m3 = NULL;
    int arows, acols, brows, bcols = 0;

    // Variables for measuring execution time
    double start, end, elapsed;

    // Record the start time
    GET_TIME(start);

    // Initialize matrices from input files
    initialize_from_file(&m1, &arows, &acols, infile1);
    initialize_from_file(&m2, &brows, &bcols, infile2);

    // Check if the matrix dimensions are compatible for multiplication
    if (acols != brows) {
        printf("Error: matrices are not the correct size.");
        exit(1);
    }

    // Allocate memory for the result matrix
    allocate2d(&m3, arows, bcols);

    // Perform matrix multiplication
    mul_matrix(m1, m2, m3, arows, bcols, acols);

    // Write the result matrix to an output file
    write_to_file(m3, arows, bcols, outfile);

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
