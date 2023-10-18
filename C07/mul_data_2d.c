// Author: Michael Dandrea
// Class: CSCI 207
// Date: 10/16/2023
// Updated: 10/17/2023
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "utilities.h"
#include "timer.h"

// Function to display the usage information for the program.
void usage(char **argv)
{
    printf("Usage: %s -a <in file1> -b <in file2> -c <out filename> [-p]\n", argv[0]);
}

// Function to parse command-line arguments and update filenames and the print flag through pointers.
void parse(int argc, char *argv[], char **afile, char **bfile, char **outfile, int *pFlag)
{
    *afile = NULL;
    *bfile = NULL;
    *outfile = NULL;
    *pFlag = 0; // Initialize the print flag to 0 (off).

    int opt;
    while ((opt = getopt(argc, argv, "a:b:c:p")) != -1)
    {
        switch (opt)
        {
        case 'a':
            *afile = optarg;
            break;
        case 'b':
            *bfile = optarg;
            break;
        case 'c':
            *outfile = optarg;
            break;
        case 'p':
            *pFlag = 1; // Set the print flag to 1 if the '-p' option is provided.
            break;
        default:
            usage(argv);
            exit(1);
        }
    }
}

int main(int argc, char **argv)
{
    char *afile = NULL;  // Initialize the first input file name to NULL.
    char *bfile = NULL;  // Initialize the second input file name to NULL.
    char *outfile = NULL; // Initialize the output file name to NULL.
    int pFlag = 0;   // Initialize the print flag to 0 (off).

    // Parse command-line arguments and update filenames and the print flag through pointers.
    parse(argc, argv, &afile, &bfile, &outfile, &pFlag);

    // Check if the input file names and output file name are provided
    if (afile == NULL || bfile == NULL || outfile == NULL)
    {
        usage(argv);
        exit(1);
    }

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
    initialize_from_file(&m1, &arows, &acols, afile);
    initialize_from_file(&m2, &brows, &bcols, bfile);

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

    // Print the result matrix if the print flag is set
    if (pFlag)
    {
        printf("Matrix 1:\n");
        print(m1, arows, acols);
        printf("Matrix 2:\n");
        print(m2, brows, bcols);
        printf("Matrix 3:\n");
        print(m3, arows, bcols);
    }

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
