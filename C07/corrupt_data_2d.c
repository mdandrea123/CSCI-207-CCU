// Author: Michael Dandrea
// Class: CSCI 207
// Date: 10/18/2023
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "utilities.h"
#include "timer.h"

int main(int argc, char **argv)
{

    srand(time(NULL)); // Seed the random number generator
    // Declare variables for matrices and their dimensions

    dtype **m1 = NULL;
    dtype **m2 = NULL;
    int rows = 0;
    int cols = 0;


    // Variables for measuring execution time
    double start, end, elapsed;

    char *infile = NULL;
    char *outfile = NULL;
    int crow = -1;
    int ccol = -1;
    int cbit = -1;
    int pflag = 0;

    // Parse command line arguments and store input file name, output file name, and print flag in variables
    parseCorrupt(argc, argv, &infile, &outfile, &pflag, &crow, &ccol, &cbit);

    if(infile == NULL || outfile == NULL)
    {
        printf("Usage: [-p] -i <in file> [-x <row index>] [-y <col index>] [-z <bit position>] -o <output filename>\n");
        exit(1);
    }

    

    // Record the start time
    GET_TIME(start);

    // Initialize a matrix from the input file
    initialize_from_file(&m1, &rows, &cols, infile);
    
    if(crow == -1){
        crow = rand() % rows;
        printf("%d\n", crow);
    }

    if(ccol == -1){
        ccol = rand() & cols - 1;
        printf("%d\n", ccol);
    }

    if(cbit == -1){
        cbit = rand() % 32;
        printf("%d\n", cbit);
    }
   
    //exit(0);

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
