#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "utilities.h"
#include "timer.h"

int main(int argc, char **argv)
{
    char *afile = NULL;  // Initialize the first input file name to NULL.
    char *bfile = NULL;  // Initialize the second input file name to NULL.
    char *outfile = NULL; // Initialize the output file name to NULL.
    int pFlag = 0;   // Initialize the print flag to 0 (off).
    int rowIndex = -1;
    int colIndex = -1;
    int bit = -1;
    int term = -1;

    // Parse command-line arguments and update filenames and the print flag through pointers.
    parseMultFaulty(argc, argv, &afile, &bfile, &outfile, &pFlag, &rowIndex, &colIndex, &bit, &term);

    if(afile == NULL || bfile == NULL || outfile == NULL)
    {
        printf("Usage: [-p] -a <in file1> -b <in file2> -c <out filename>\n");
        exit(1);
    }
    srand(time(NULL));

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
    if (rowIndex > arows || colIndex > bcols){
        printf("Row index and column index must be less than the number of rows of A and columns of B, respectively.");
        exit(1);
    }
    if(bit > 31 || (bit < 0 && bit != -1)){
        printf("Bit must be between 0 and 31.");
        exit(1);
    }
    if (term > acols || (term < 0 && term != -1)){
        printf("Term must be less than or equal the number of columns of A.");
        exit(1);
    }
    if(rowIndex == -1){
        rowIndex = rand() % arows;  
    }
    if(colIndex == -1){
        colIndex = rand() % bcols;
    }
    if(bit == -1){
        bit = rand() % 32;
    }
    if(term == -1){
        term = rand() % acols;
    }

    // Check if the matrix dimensions are compatible for multiplication
    if (acols != brows) {
        printf("Error: matrices are not the correct size.");
        exit(1);
    }

    // Allocate memory for the result matrix
    allocate2d(&m3, arows, bcols);

    // Perform matrix multiplication
    mul_matrixFaulty(m1, m2, m3, arows, bcols, acols, rowIndex, colIndex, bit, term);

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
