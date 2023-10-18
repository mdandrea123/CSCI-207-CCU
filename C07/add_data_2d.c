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
    printf("Usage: %s-a <in file1> -b <in file2> -c <out filename> [-p]\n", argv[0]);
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

    parse(argc, argv, &afile, &bfile, &outfile, &pFlag);

    if (afile == NULL || bfile == NULL || outfile == NULL)
    {
        usage(argv);
        exit(1);
    }

    dtype **m1 = NULL; // Declare a pointer to a 2D array for the first input file.
    dtype **m2 = NULL; // Declare a pointer to a 2D array for the second input file.
    dtype **m3 = NULL; // Declare a pointer to a 2D array for the output file.
    int rows = 0;      // Initialize the number of rows.
    int cols = 0;      // Initialize the number of columns.

    check_size(afile, bfile); // Check if the two input files have the same size.

    double start, end, elapsed;
    GET_TIME(start); // Start measuring the execution time.

    // Initialize 2D arrays from the input files, allocate memory for the output array, add matrices, and then free the memory.
    initialize_from_file(&m1, &rows, &cols, afile);
    initialize_from_file(&m2, &rows, &cols, bfile);
    allocate2d(&m3, rows, cols);
    add_matrices(m1, m2, m3, rows, cols, outfile);
	
	if (pFlag)
    {
        printf("Matrix 1:\n");
        print(m1, rows, cols);
        printf("Matrix 2:\n");
        print(m2, rows, cols);
        printf("Matrix 3:\n");
        print(m3, rows, cols);
    }

    free2d(&m1);
    free2d(&m2);
    free2d(&m3);

	

    GET_TIME(end); // Stop measuring the execution time.
    elapsed = end - start;
    printf("The program took %e seconds\n", elapsed); // Print the elapsed time.

    

    return 0;
}
