// Author: Michael Dandrea
// Class: CSCI 207
// Date: 10/18/2023
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "utilities.h"
#include "timer.h"

// Function to display usage information for the program
void usage(char **argv)
{
    printf("Usage: %s -i <in file> -x <row index> -y <col index> -z <bit position> -o <output filename>", argv[0]);
}

// Function to parse command line arguments and store input file name, output file name, and print flag in variables
void parse(int argc, char **argv, char **infile, char **outfile, int *pflag, int *crow, int *ccol, int *cbit)
{
    int opt;

    // Parse command line arguments using getopt
    while ((opt = getopt(argc, argv, "pi:o:x:y:z:")) != -1)
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
            case 'x':
                *crow = atoi(optarg);
                break;
            case 'y':
                *ccol = atoi(optarg);
                break;
            case 'z':
                *cbit = atoi(optarg);
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

    char *infile = NULL;
    char *outfile = NULL;
    int crow = 0;
    int ccol = 0;
    int cbit = 0;
    int pflag = 0;

    // Parse command line arguments and store input file name, output file name, and print flag in variables
    parse(argc, argv, &infile, &outfile, &pflag, &crow, &ccol, &cbit);

   
    if (cbit > 31 || cbit < 0){
        printf("Invalid bit position, must be between 0 and 31 inclusive.\n");
        exit(1);
    }

    // Record the start time
    GET_TIME(start);

    // Initialize a matrix from the input file
    initialize_from_file(&m1, &rows, &cols, infile);
     if(crow < 0 || ccol < 0 || crow > rows || ccol > cols){
        printf("Error: row and column index must be between 0 and the number rows inclusive.\n");
        exit(1);
    }

    // Allocate memory for another matrix with an extra row
    allocate2d(&m2, rows, cols);

    corrupt(m1, m2, rows, cols, crow, ccol, cbit);

    // Write the second matrix to an output file
    write_to_file(m2, rows, cols, outfile);

    // Print the second matrix if the print flag is set
    if (pflag)
    {
        printf("Matrix 1:\n");
        print(m1, rows, cols);
        printf("Matrix 2:\n");
        print(m2, rows, cols);
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
