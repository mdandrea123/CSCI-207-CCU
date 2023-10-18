// Author: Michael Dandrea
// Class: CSCI 207
// Date: 10/2/2023
#include <stdio.h>
#include <stdlib.h>
#include "utilities.h"
#include "timer.h"

// Function to display the usage information for the program.
void usage(char **argv)
{
	printf("Usage: %s <in_file1> <in_file2> <out_file>\n", argv[0]);
}

int main(int argc, char **argv)
{
	if (argc != 4)
	{
		usage(argv); // Display usage information if the number of command-line arguments is not 4.
		exit(1);
	}

	dtype **m1 = NULL;		 // Declare a pointer to a 2D array for the first input file.
	dtype **m2 = NULL;		 // Declare a pointer to a 2D array for the second input file.
	dtype **m3 = NULL;		 // Declare a pointer to a 2D array for the output file.
	int rows = 0;			 // Initialize the number of rows.
	int cols = 0;			 // Initialize the number of columns.
	char *afile = argv[1];	 // Store the first command-line argument as the first input file name.
	char *bfile = argv[2];	 // Store the second command-line argument as the second input file name.
	char *outfile = argv[3]; // Store the third command-line argument as the output file name.
	double start;
	double end;
	double elapsed;
	check_size(afile, bfile); // Check if the two input files have the same size.
	GET_TIME(start);		  // Start measuring the execution time.

	// Initialize 2D arrays from the input files, allocate memory for the output array, add matrices, and then free the memory.
	initialize_from_file(&m1, &rows, &cols, afile);
	initialize_from_file(&m2, &rows, &cols, bfile);
	allocate2d(&m3, rows, cols);
	add_matrices(m1, m2, m3, rows, cols, outfile);
	free2d(&m1);
	free2d(&m2);
	free2d(&m3);

	GET_TIME(end); // Stop measuring the execution time.
	elapsed = end - start;
	printf("The program took %e seconds\n", elapsed); // Print the elapsed time.

	return 0;
}
