// Author: Michael Dandrea
// Class: CSCI 207
// Date: 10/16/2023
// Updated: 10/17/2023
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "utilities.h"
#include "timer.h"

// Function to display usage information for the program
void usage(char **argv)
{
    printf("Usage: %s -i <in file> -o <out filename> [-p]", argv[0]);
}

// Function to parse command line arguments and store input file name, output file name, and print flag in variables
void parse(int argc, char **argv, char **infile, char **outfile, int *pflag)
{
    int opt;

    // Parse command line arguments using getopt
    while ((opt = getopt(argc, argv, "pi:o:")) != -1)
    {
        switch (opt)
        {
            case 'p':
                *pflag = 1;
                break;
            case 'i':
                *infile = optarg;
                break;
            case 'o':
                *outfile = optarg;
                break;
            default:
                usage(argv);
                exit(1);
        }
    }

    // Check if the input file and output file are provided
    if (*infile == NULL || *outfile == NULL)
    {
        usage(argv);
        exit(1);
    }
}

int main(int argc, char **argv)
{
    // Declare variables for matrices and their dimensions
    dtype **m1 = NULL;
    dtype **m2 = NULL;
    int rows = 0;
    int cols = 0;

    // Variables for measuring execution time
    double start, end, elapsed;

    // Declare variables for input file name, output file name, and print flag
    char *infile = NULL;
    char *outfile = NULL;
    int pflag = 0;

    // Parse command line arguments and store input file name, output file name, and print flag in variables
    parse(argc, argv, &infile, &outfile, &pflag);

    // Record the start time
    GET_TIME(start);

    // Initialize a matrix from the input file
    initialize_from_file(&m1, &rows, &cols, infile);

    // Allocate memory for another matrix with an extra row
    allocate2d(&m2, rows + 1, cols);

    // Calculate column checksums and store them in the second matrix
    col_checksum(m1, m2, rows, cols);

    // Write the second matrix to an output file
    write_to_file(m2, rows + 1, cols, outfile);

    // Print the second matrix if the print flag is set
    if (pflag)
    {
        printf("Matrix 1:\n");
        print(m1, rows, cols);
        printf("Matrix 2:\n");
        print(m2, rows + 1, cols);
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
