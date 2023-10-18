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
    printf("Usage: %s -i <input filename> [-p]\n", argv[0]);
}

// Function to parse command-line arguments and update a pointer to the input file name.
void parse(int argc, char *argv[], char **fname)
{
    *fname = NULL; // Initialize the input file name to NULL.
    
    int opt;
    while ((opt = getopt(argc, argv, "i:")) != -1)
    {
        switch (opt)
        {
        case 'i':
            *fname = optarg;
            break;
        default:
            usage(argv);
            exit(1);
        }
    }
}

int main(int argc, char *argv[])
{
    char *fname; // Declare a pointer to the input file name.

    parse(argc, argv, &fname);

    if (fname == NULL)
    {
        usage(argv);
        exit(1);
    }

    dtype **matrix;
    int rows = 0;
    int cols = 0;
    
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
